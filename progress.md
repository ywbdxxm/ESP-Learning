# Progress: ESP-Learning AI Manual Reference Setup

## 2026-04-12

- Inspected `/home/qcgg/workspace/ESP-Learning` repository status and existing files.
- Confirmed processed ESP32-S3 manual artifacts in `/home/qcgg/workspace/convert-pdf/manuals/processed`.
- Added root `AGENTS.md` to make future Codex sessions proactively consult ESP32-S3 manual artifacts.
- Added `doc/ai-esp32-manual-reference.md` with exact paths, usage workflow, and common search commands.
- Added planning files for this repository: `task_plan.md`, `findings.md`, and `progress.md`.
- Created global Codex skill `/home/qcgg/.codex/skills/esp32-manual-reference/SKILL.md`.
- Slimmed `AGENTS.md` to reference the skill instead of embedding the full manual lookup workflow.
- Kept `doc/ai-esp32-manual-reference.md` as a compact fallback reference.
- Verified ESP32-S3 processed manual manifest/alerts paths are readable from ESP-Learning.
- Verified `rg` can search the ESP32-S3 TRM sections index from ESP-Learning.
- Ready to commit only AGENTS/README/manual-reference/planning files; existing untracked project directories are intentionally left untouched.
- Started ESP32-S3 DMA/GDMA manual research.
- Confirmed existing planning files are present and will be appended rather than replaced.
- Verified local manual-access tooling availability: `rg`, `jq`, `sed`, `awk`, `pdftotext`, `pdfinfo`, `pdftoppm`, `python3`.
- Re-checked TRM manifest and alerts with `jq`; DMA-relevant sections/tables are readable.
- Located and cross-checked:
  - TRM Chapter 3 `GDMA Controller (GDMA)` pages `357-398`
  - TRM `System and Memory` GDMA address-space notes pages `406-407`
  - TRM `Permission Control` GDMA/PMS notes pages `697-701`
  - representative peripheral DMA notes for `UART/UHCI`, `AES`, `RMT`, `ADC`, `USB OTG`, and `SDHOST`
- Reviewed current `AGENTS.md` and `README.md` for role overlap and missing repository positioning.
- Refreshed the repository entry docs so `README.md` is human-facing and `AGENTS.md` stays Codex-facing.
- Reviewed current root `.gitignore` and confirmed it is too broad because it uses `.*`.
- Confirmed the intended ignore policy is to ignore personal/editor/local-environment files globally.
- Confirmed current branch is `main` and remote is `origin git@github.com:ywbdxxm/ESP-Learning.git`.
- Replaced root `.gitignore` with explicit OS/editor/cache/build/ESP-IDF ignore rules.
- Verified ignore behavior with `git status --short --ignored`; local dot-configs and build outputs are ignored while project content remains visible.
- Committed current tracked doc/planning updates and root `.gitignore` as `99dbd55 docs: refresh repo docs and root gitignore`.
- Pushed commit `99dbd55` to `origin/main`.
