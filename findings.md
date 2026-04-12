# Findings: ESP-Learning AI Manual Reference Setup

## Current Repository State

- Repository path: `/home/qcgg/workspace/ESP-Learning`
- Branch: `main`
- Existing tracked file before setup: `README.md`
- Several ESP learning directories already exist but are currently untracked:
  - `ESP32-S3/`
  - `doc/`
  - `img/`
  - `prj/`
  - `settings/`

## Processed Manual Sources

The canonical processed ESP32-S3 manual artifacts live in:

- `/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-datasheet-en`
- `/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en`

The source architecture document is:

- `/home/qcgg/workspace/convert-pdf/docs/architecture/2026-04-12-docling-embedded-manual-processing.md`

## Manual Quality Notes

### ESP32-S3 Datasheet

- `status = success`
- `page_count = 87`
- `table_count = 71`
- `chunks = 309`
- `sections = 141`
- `alert_count = 1`
- Known alert: `Table 2-9. Peripheral Pin Assignment` table body fell back to an image.

### ESP32-S3 Technical Reference Manual

- `status = success`
- `page_count = 1531`
- `window_count = 7`
- `table_count = 667`
- `chunks = 3775`
- `sections = 1379`
- `alert_count = 9`
- Known alert type: `empty_table_sidecar`

## Best Practice Decision

Do not copy converted manual artifacts into ESP-Learning. Use absolute references to the canonical processed outputs in `convert-pdf`.

This keeps:

- one source of truth for manual conversion
- one update path when Docling output changes
- ESP-Learning focused on firmware learning and ESP-IDF code

Future Codex sessions should use `AGENTS.md` and `doc/ai-esp32-manual-reference.md` to find and query the processed manual artifacts.

## Skill Migration

The detailed ESP32-S3 manual lookup workflow now lives in:

- `/home/qcgg/.codex/skills/esp32-manual-reference/SKILL.md`

Reason:

- It is reusable across ESP32 projects.
- It can be triggered by ESP32/ESP-IDF/register/peripheral task wording.
- It avoids making `AGENTS.md` increasingly large.
- `ESP-Learning/AGENTS.md` should stay as a thin pointer to the skill plus project-specific code editing rules.

`doc/ai-esp32-manual-reference.md` remains as a local fallback reference for humans or sessions where the skill is unavailable.

## ESP32-S3 DMA Research

### Local Tooling for Manual Access

- `rg` is available for fast text search in `sections.jsonl` and `chunks.jsonl`.
- `jq` is available for structured filtering of `manifest.json`, `alerts.json`, and JSONL indices.
- `sed` and `awk` are sufficient for quick table/CSV/context inspection.
- `pdftotext`, `pdfinfo`, and `pdftoppm` are available for cross-checking suspicious processed output against the original PDF.
- With these tools present, the local ESP32-S3 manuals are fully workable as a documentation database.

### TRM Coverage and Quality for DMA Work

- ESP32-S3 TRM processed artifact:
  - `status = success`
  - `page_count = 1531`
  - `table_count = 667`
  - `alert_count = 9`
- Current alert type is only `empty_table_sidecar`; the primary GDMA tables used in this research are present and readable.

### ESP32-S3 GDMA Core Facts

- GDMA chapter is `Chapter 3 GDMA Controller (GDMA)`, pages `357-398` in the TRM.
- GDMA provides:
  - peripheral-to-memory transfer
  - memory-to-peripheral transfer
  - memory-to-memory transfer
- GDMA has `10` independent channels:
  - `5` transmit channels
  - `5` receive channels
- Official GDMA-capable clients listed in Chapter 3:
  - `SPI2`
  - `SPI3`
  - `UHCI0`
  - `I2S0`
  - `I2S1`
  - `LCD/CAM`
  - `AES`
  - `SHA`
  - `ADC`
  - `RMT`
- DMA-capable `UART0/1/2` traffic is routed through `UHCI0`, not by attaching UART directly to GDMA.

### Descriptor and Channel Model

- GDMA uses linked lists stored in internal RAM.
- Each descriptor is `3 words`:
  - `DW0`: owner / suc_eof / err_eof / length / size
  - `DW1`: buffer address
  - `DW2`: next descriptor address
- The next-descriptor pointer (`DW2`) must point to internal RAM.
- Owner semantics:
  - `0`: CPU owns buffer
  - `1`: GDMA owns buffer
- `suc_eof` on transmit can be used to mark transfer phase end and generate completion behavior.
- `err_eof` is meaningful only for `UHCI0` receive path.

### Reachable Memory and Address Windows

- `System and Memory` chapter says GDMA uses the same address view as the CPU data bus for:
  - `Internal SRAM1`: `0x3FC8_8000 ~ 0x3FCE_FFFF`
  - `Internal SRAM2`: `0x3FCF_0000 ~ 0x3FCF_FFFF`
  - `External RAM`: `0x3C00_0000 ~ 0x3DFF_FFFF`
- GDMA cannot access the internal SRAM blocks currently occupied by cache.
- TRM states GDMA internal-RAM addressability is at most `480 KB`.
- External memory access for GDMA is RAM-only. Flash access for DMA is not described as a GDMA path.

### Alignment and Burst Rules

- Internal RAM:
  - burst mode is optional
  - when burst mode is disabled, buffer address/size/length do not need word alignment
  - when burst mode is enabled, receive descriptors require word alignment for `size` and `buffer address`
- External RAM:
  - GDMA works only in burst mode
  - block size can be `16 / 32 / 64` bytes
  - receive descriptors require block-aligned `size` and `buffer address`
  - receive data shorter than block size is padded with `0` for the burst; valid received length must be read from descriptor `length`

### Arbitration and Throughput

- GDMA uses fixed-priority arbitration across channels.
- Priority range is `0 ~ 9`; larger number means higher priority.
- Same-priority channels fall back to round-robin arbitration.
- TRM explicitly calls out high-speed/low-latency users like `SPI` and `LCD/CAM` as motivation for channel priority.

### Permission Control

- External SRAM available to GDMA is split into four regions:
  - `Region0`: inaccessible to peripherals via GDMA
  - `Region1`: configurable GDMA access
  - `Region2`: configurable GDMA access
  - `Region3`: inaccessible to peripherals via GDMA
- Region boundaries are offsets from `0x3C000000` in units of `4 KB`.
- Access to Region1/Region2 is configured per GDMA-capable peripheral via PMS registers.
- Unauthorized internal-memory access via GDMA can raise `DMA_APB_PMS_MONITOR_VIOLATE_INTR`.
- Unauthorized external-memory access is logged via GDMA reject status/address registers.

### Peripheral-Specific DMA Notes

- `UART`:
  - all three UART controllers share one TX/RX GDMA channel through `UHCI0`
  - UART GDMA mode is tied to HCI packet encode/decode logic
- `AES`:
  - DMA-AES mode reads source blocks from DMA and writes result back through DMA
  - source length must be `128-bit` aligned or padded
- `RMT`:
  - not every channel is DMA-capable
  - channel `3` supports DMA for TX-side access
  - channel `7` supports DMA for RX-side access
  - DMA and APB ownership rules are explicit; violating them can cause access-fail/error interrupts
- `ADC`:
  - DIG ADC1 supports DMA through peripheral DMA path and emits 32-bit DMA words
- `GP-SPI2/3`:
  - DMA-controlled transfers use GDMA TX/RX buffers
  - for several slave modes, TRM recommends waiting on `GDMA_IN_SUC_EOF_CHn_INT` instead of only SPI-side done interrupts

### DMA Taxonomy on ESP32-S3

- The main SoC-wide DMA engine is `GDMA` in Chapter 3.
- Not every DMA mention in the TRM means GDMA:
  - `USB OTG` has its own internal DMA modes (`Buffer DMA`, `Scatter/Gather DMA`)
  - `SD/MMC Host` has its own descriptor-based DMA controller/IDMAC
- For driver reading and debugging, it is important to distinguish:
  - GDMA-backed peripheral DMA
  - peripheral-local DMA engines
  - cache-mediated external-memory access

## Repository Entry Docs Refresh

- `README.md` should be the human-facing entry point for this repository.
- `AGENTS.md` should stay brief and machine-oriented for Codex.
- The repository is not just a manual-reference demo directory; it should be described as an `ESP32 / ESP-IDF` learning and development workspace.
- The two files should avoid repeating the same AI/manual workflow wording.
- The updated split should be:
  - `README.md`: repository purpose, focus, and doc entry points
  - `AGENTS.md`: repository context, ESP32-S3 lookup rule, ESP-IDF editing boundaries, planning-file rule

## Root Gitignore Refresh

- Current root `.gitignore` content is:
  - `build`
  - `.*`
- The pattern `.*` is too broad for a development repository because it hides all dotfiles and dot-directories indiscriminately.
- Desired root `.gitignore` strategy:
  - ignore local editor directories such as `.vscode/`, `.idea/`, `.devcontainer/`
  - ignore local build outputs such as `build/`, `CMakeFiles/`, `CMakeCache.txt`
  - ignore local ESP-IDF outputs such as `sdkconfig`, `sdkconfig.old`, `managed_components/`, `.espressif/`
  - ignore local caches and temporary files such as `.cache/`, `__pycache__/`, `*.pyc`, swap files, and OS metadata
  - do not keep a blanket `.*` rule
- Root `.gitignore` should only manage repository-wide local artifacts.
- Existing subproject `.gitignore` files should not be rewritten as part of this step.
- Verification result after replacement:
  - local directories such as root `.vscode/` are ignored
  - nested local files/directories such as `prj/hello_world/.clangd`, `.devcontainer/`, `.vscode/`, `build/`, `sdkconfig`, and `prj/sample_project/.cache/` are ignored
  - non-dot project content such as `doc/`, `img/`, `prj/`, and `settings/` remains visible to git
