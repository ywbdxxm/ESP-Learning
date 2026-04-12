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
