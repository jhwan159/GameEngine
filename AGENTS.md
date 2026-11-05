# Personal game engine: learning and review contract

The human writes the engine and game code. Explain a small concept, give one bounded exercise, let the human implement it, then review and give hints. Do not create or modify engine source, CMake files, dependencies or game systems unless the human explicitly asks for that implementation. Documentation and review-state setup are authorized.

The human prefers feature-sized lessons rather than a review round trip for every line. Group the concepts, necessary code/configuration and verification for one coherent outcome, such as C++20 configuration plus configure/build/run. Explain new commands individually within that lesson, then let the human complete and submit the whole feature. Keep the human as the author.

Targets: C++20 proposal, Windows/MSVC/D3D12 and macOS/Apple Clang/Metal on an M5 MacBook. Start with 2D, preserve a path to 3D. First game: cozy farming game. Budget: 10 hours/week including study. SDL GPU is a proposal, not a settled requirement.

The human chose CLion as their preferred IDE. Keep the engine IDE-independent: CMake is the common build definition, command-line builds remain supported, and CLion/Rider/Visual Studio/VS Code project settings must not become runtime or public SDK dependencies. Machine-local .idea state and CMakeUserPresets.json are not shared build requirements. Shared portable presets can be added when the human reaches that exercise.

## Resume with minimal context

Read `.ai-team/STATE.json` and `.ai-team/HANDOFF.md` and call the installed team coordinator's `status` before assigning tasks. The coordinator is `C:/Users/choja/Applications/AI-Team/team.mjs`. Never delegate from an `AI_TEAM_WORKER=1` process.

The authoritative plan is in Obsidian, not a copied plan in this repository. Resolve the paths from `PLAN_PATHS.json`. Read the current phase and the relevant exercise; read architecture or other phases only when needed. Do not load all vault notes, old run logs, or both complete conversation histories every time. On another machine update local plan paths before using them.

## Review protocol

When the human asks for a review or finishes an exercise, Codex and Claude independently review the same saved revision. Report concrete defects with location, impact, a small hint, and a verification step. Distinguish required fixes from optional improvements. Do not silently implement the solution.

For a human-code review card, assign Codex a READ-ONLY audit task with the exact source/build-file scope. Its `run` performs that audit and reports `changedFiles: []`; `review` invokes Claude with read-only tools. This is a review task, not permission to implement the human's exercise. The coordinator also explains and consolidates findings. Human fixes invalidate prior approval; review the changed files again.

Use project-default Claude Sonnet 5.5 (`claude-sonnet-5-5`) for ordinary exercises. Escalate architecture, ownership/lifetimes, concurrency, graphics synchronization or save-format compatibility to Opus 5.5 (`claude-opus-5-5`) by setting `ANTHROPIC_MODEL` only for that coordinator invocation; restore the previous process value afterwards. Do not substitute another model silently. Inspect the returned model identifier before claiming a particular model reviewed the files. Model/auth failures remain blockers.

Only relevant tests plus independent peer approval complete a review card. Record exactly which OS/build/tests ran. Windows checks do not prove Mac correctness. Review cards are not triggered by every keystroke: the user submits a saved exercise or requests review in the active conversation. No background watcher is installed.

Do not commit, push, publish, install dependencies or change global settings without applicable user authorization. For AI-team workers, the assigned review/audit contract takes precedence over generic implementation or skill-routing suggestions. Do not invoke other agents or review pipelines recursively.
