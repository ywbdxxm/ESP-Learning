# Task Plan: ESP-Learning AI Manual Reference Setup

## Goal

Configure `/home/qcgg/workspace/ESP-Learning` so Codex can proactively use the ESP32-S3 datasheet and technical reference manual artifacts produced by `/home/qcgg/workspace/convert-pdf` during ESP32/ESP-IDF development.

## Current Phase

ESP32 Manual Reference Skill Migration Complete

## Phases

### Phase 1: Inspect Existing Repository
- [x] Check repository status and existing tracked files
- [x] Confirm existing README and absence of root `AGENTS.md`
- [x] Confirm processed ESP32-S3 manual artifact paths in `convert-pdf`
- **Status:** complete

### Phase 2: Configure Codex Manual Access
- [x] Add root `AGENTS.md` with mandatory ESP32-S3 lookup workflow
- [x] Add `doc/ai-esp32-manual-reference.md` with exact processed manual paths and usage commands
- [x] Update `README.md` as a short entry point
- **Status:** complete

### Phase 3: Move Manual Lookup Rules Into Codex Skill
- [x] Create `~/.codex/skills/esp32-manual-reference/SKILL.md`
- [x] Slim root `AGENTS.md` to reference the skill instead of duplicating the full workflow
- [x] Keep `doc/ai-esp32-manual-reference.md` as fallback local reference
- **Status:** complete

## Decisions Made

| Decision | Rationale |
| --- | --- |
| Reference processed manuals by absolute path instead of copying them | Avoid duplicating large generated artifacts and keep `convert-pdf` as the canonical update path |
| Use root `AGENTS.md` for future Codex behavior | Codex can automatically read repository guidance when working in this directory |
| Keep a human-readable reference document in `doc/` | Developers can inspect and update the paths/workflow without reading all agent instructions |
| Require original PDF cross-check for hardware-critical facts | Converted artifacts are useful but not authoritative |
| Put the detailed lookup workflow in a Codex skill instead of `AGENTS.md` | Skills can be triggered by task wording and avoid making per-repository `AGENTS.md` files increasingly large |

## Current ESP32-S3 References

- Datasheet processed root: `/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-datasheet-en`
- TRM processed root: `/home/qcgg/workspace/convert-pdf/manuals/processed/esp32-s3-technical-reference-manual-en`
- Codex skill: `/home/qcgg/.codex/skills/esp32-manual-reference/SKILL.md`
- Reference workflow: `doc/ai-esp32-manual-reference.md`
