# Repository Guidance

## Project Context

This repository is for ESP32 learning and ESP-IDF development.

## ESP32 Manual Lookup

For ESP32-S3 hardware facts, register-level work, ESP-IDF peripheral configuration, pin mapping, timing, electrical limits, clocks, interrupts, or debugging, use the Codex skill:

- `esp32-manual-reference`

If the skill is unavailable, use the local fallback reference:

- `doc/ai-esp32-manual-reference.md`

Do not rely on memory alone for hardware-critical ESP32-S3 details. Cross-check register values, bit definitions, pin mappings, timing limits, and electrical characteristics against the processed manuals and original PDF pages.

## Editing ESP-IDF Code

- Prefer existing ESP-IDF project structure and local `CMakeLists.txt` / `sdkconfig` conventions.
- Do not modify generated `build/` directories unless explicitly asked.
- Include manual page references in final explanations when a change depends on ESP32-S3 hardware behavior.

## Planning With Files

For multi-step work in this repository, maintain:

- `task_plan.md`
- `findings.md`
- `progress.md`
