# Repository Guidance

## Project Context

This repository is an ESP32 / ESP-IDF learning and development workspace.

It can contain:

- ESP32 bring-up and peripheral experiments
- ESP-IDF practice projects
- driver and register-level investigation
- notes and small development prototypes

## ESP32 Manual Lookup

For ESP32-S3 hardware facts, register-level work, ESP-IDF peripheral configuration, pin mapping, timing, electrical limits, clocks, interrupts, or debugging, use the Codex skill:

- `esp32-manual-reference`

If the skill is unavailable, use the local fallback reference:

- `doc/ai-esp32-manual-reference.md`

Do not rely on memory alone for hardware-critical ESP32-S3 details. Cross-check register values, bit definitions, pin mappings, timing limits, electrical characteristics, DMA constraints, and other hardware-critical facts against the processed manuals and original PDF pages.

## Editing ESP-IDF Code

- Prefer existing ESP-IDF project structure and local `CMakeLists.txt` / `sdkconfig` conventions.
- Do not modify generated `build/` directories unless explicitly asked.
- Keep changes aligned with the learning or development purpose of the target subproject.
- Include manual page references in final explanations when a change depends on ESP32-S3 hardware behavior.

## Planning With Files

For multi-step work in this repository, maintain:

- `task_plan.md`
- `findings.md`
- `progress.md`
