# AI ESP32-S3 Manual Reference Workflow

Date: 2026-04-12

## Purpose

This document configures ESP-Learning so future Codex sessions can proactively use the ESP32-S3 manuals processed by the sibling `convert-pdf` repository.

The goal is not to copy converted manuals into this repository. The processed artifacts are large and are already maintained in one canonical location. ESP-Learning should reference them by absolute path.

## Canonical Processed Manuals

### ESP32-S3 Datasheet

Processed root:

```text
/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-datasheet-en
```

Original PDF:

```text
/home/qcgg/workspace/convert-pdf/manuals/raw/espressif/esp32s3/esp32-s3_datasheet_en.pdf
```

Current observed status:

- `status = success`
- `page_count = 87`
- `table_count = 71`
- `chunks = 309`
- `sections = 141`
- `alert_count = 1`

Known alert:

- `Table 2-9. Peripheral Pin Assignment` table body fell back to an image.

Use this manual for:

- electrical characteristics
- package/pin overview
- boot strapping and boot mode basics
- recommended operating conditions
- high-level peripheral feature summary
- RF and power figures

### ESP32-S3 Technical Reference Manual

Processed root:

```text
/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en
```

Original PDF:

```text
/home/qcgg/workspace/convert-pdf/manuals/raw/espressif/esp32s3/esp32-s3_technical_reference_manual_en.pdf
```

Current observed status:

- `status = success`
- `page_count = 1531`
- `window_count = 7`
- `table_count = 667`
- `chunks = 3775`
- `sections = 1379`
- `alert_count = 9`

Known alert type:

- `empty_table_sidecar`

Use this manual for:

- register summaries
- register bit descriptions
- peripheral architecture
- GPIO Matrix / IO MUX
- I2C / SPI / UART / TWAI / USB / timers / interrupts
- clock/reset/power internals
- low-level driver and debugging details

## How Future AI Should Work

When asked to implement or debug ESP32-S3 code, the AI should not rely on memory alone.

Recommended sequence:

1. Start with the relevant processed root's `manifest.json`.
2. Check `alerts.json` if `alert_count > 0`.
3. Search `sections.jsonl` for the relevant chapter or peripheral.
4. Search `chunks.jsonl` for concrete facts and page citations.
5. Read `document.md` for local context.
6. Use `tables/*.csv` or `tables/*.html` for table values.
7. Use `document.html`, `artifacts/`, and the original PDF for diagrams and suspicious pages.
8. For hardware-critical facts, cite the page and cross-check the original PDF.

## Common Search Commands

Find a peripheral chapter or topic:

```sh
rg -n "GPIO Matrix|IO MUX|I2C Controller|UART Controller|SPI Controller|Interrupt Matrix" \
  /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en/sections.jsonl
```

Find register names:

```sh
rg -n "GPIO_FUNC0_IN_SEL_CFG_REG|UART_FIFO_REG|I2C_SCL_LOW_PERIOD_REG" \
  /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en/chunks.jsonl
```

Find datasheet constraints:

```sh
rg -n "Recommended Operating Conditions|Absolute Maximum Ratings|Boot Mode|Peripheral Pin Assignment" \
  /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-datasheet-en/chunks.jsonl
```

Inspect quality alerts:

```sh
cat /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-datasheet-en/alerts.json
cat /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en/alerts.json
```

## Best Practice

The processed manuals should be treated as a local documentation database for Codex:

- `chunks.jsonl` for fast retrieval
- `sections.jsonl` for navigation
- `document.md` for reading context
- `tables/` for values
- `artifacts/` and original PDF for diagrams and final checks
- `alerts.json` for parser limitations

Do not copy these artifacts into ESP-Learning. Keep them in `convert-pdf` so they have one canonical source and one update path.

## When To Reprocess Manuals

Reprocess in `convert-pdf` when:

- the source PDF changes
- a new ESP32-S3 manual is added
- Docling conversion code changes in a way that affects outputs
- `alerts.json` indicates a known limitation that a new parser/tool may handle better

Do not reprocess from ESP-Learning unless the task is explicitly about the PDF processing pipeline.
