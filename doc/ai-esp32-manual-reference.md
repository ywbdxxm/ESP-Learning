# AI ESP32-S3 Manual Reference

This is the ESP-Learning fallback reference for ESP32-S3 manual lookup.

Preferred mechanism: use the Codex skill `esp32-manual-reference` from:

```text
/home/qcgg/.codex/skills/esp32-manual-reference/SKILL.md
```

## Canonical Processed Manuals

Datasheet:

```text
/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-datasheet-en
```

Technical Reference Manual:

```text
/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en
```

Original PDFs:

```text
/home/qcgg/workspace/convert-pdf/manuals/raw/espressif/esp32s3/esp32-s3_datasheet_en.pdf
/home/qcgg/workspace/convert-pdf/manuals/raw/espressif/esp32s3/esp32-s3_technical_reference_manual_en.pdf
```

## Lookup Order

1. Read `<manual-root>/manifest.json`.
2. Check `alerts.json`.
3. Search `sections.jsonl` for navigation.
4. Search `chunks.jsonl` for facts and page citations.
5. Read `document.md` for surrounding context.
6. Use `tables/*.csv` / `tables/*.html` for table values.
7. Use `document.html`, `artifacts/`, and the original PDF for diagrams and final verification.

## Useful Commands

```sh
rg -n "GPIO Matrix|IO MUX|I2C Controller|UART Controller|SPI Controller|Interrupt Matrix" \
  /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en/sections.jsonl

rg -n "GPIO_FUNC0_IN_SEL_CFG_REG|UART_FIFO_REG|I2C_SCL_LOW_PERIOD_REG" \
  /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en/chunks.jsonl

rg -n "Recommended Operating Conditions|Absolute Maximum Ratings|Boot Mode|Peripheral Pin Assignment" \
  /home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-datasheet-en/chunks.jsonl
```

## Known Caveats

- Datasheet: `Table 2-9. Peripheral Pin Assignment` table body fell back to an image.
- TRM: some table sidecars are flagged as `empty_table_sidecar`.
- Processed artifacts are lookup aids. Original PDFs remain authoritative.
