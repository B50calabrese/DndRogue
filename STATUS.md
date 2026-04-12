# Project Status: DndRogue

This file tracks the current progress, state of the game, and infrastructure. **All agents are required to update this file as the final step of their task.**

## Most Recent Changes
- Added project status tracking system (`STATUS.md` and `AGENTS.md` updates).
- Initial project skeleton created.
- `GameEngine` submodule integrated.
- Core application lifecycle (`DndRogueApp`) established.
- Stub implementations for major game scenes: `MainMenuScene`, `StartRunScene`, `OverworldScene`, `BattleScene`, `MenuScene`.

## Current State of Infrastructure

### Core Application (`DndRogueApp`)
- **Lifecycle**: `OnInit`, `OnUpdate`, and `OnShutdown` are implemented.
- **Scene Management**: `OnInit` correctly initializes the `MainMenuScene` using the `engine::SceneManager`.
- **Status**: Functional skeleton. `OnUpdate` and `OnShutdown` contain logging but no complex logic yet.

### GameEngine Integration
- **Submodule**: Linked and configured in `CMakeLists.txt`.
- **Dependencies**: GLFW, OpenGL, and FreeType are required and expected to be provided by the environment/engine.
- **Status**: Integrated.

## Major Scenes Technical Breakdown

### MainMenuScene
- **Intent**: Entry point for navigation.
- **Lifecycle Methods**:
  - [x] `OnAttach`: Implemented full UI setup with ECS.
  - [x] `OnDetach`: Logging implemented.
  - [x] `OnUpdate`: Logic handled by ECS UI systems.
  - [x] `OnRender`: Rendering handled by `UIRenderSystem`.
  - [x] `OnInput`: Input handled by `UIInputSystem`.
- **Features**:
  - [x] Menu selection logic (Hover effects, Click events).
  - [x] UI Rendering (Start run, Exit buttons).
  - [x] Input handling for navigation and application exit.

### StartRunScene
- **Intent**: Character selection and run configuration.
- **Lifecycle Methods**:
  - [x] `OnAttach`: Logging implemented.
  - [x] `OnDetach`: Logging implemented.
  - [ ] `OnUpdate`: Stub.
  - [ ] `OnRender`: Stub.
  - [ ] `OnInput`: Stub.
- **Features**:
  - [ ] Character selection UI.
  - [ ] Difficulty/Option configuration.

### OverworldScene
- **Intent**: Roguelike map exploration.
- **Lifecycle Methods**:
  - [x] `OnAttach`: Logging implemented.
  - [x] `OnDetach`: Logging implemented.
  - [ ] `OnUpdate`: Stub.
  - [ ] `OnRender`: Stub.
  - [ ] `OnInput`: Stub.
- **Features**:
  - [ ] Map generation/loading.
  - [ ] Player movement on map.
  - [ ] Event trigger logic.

### BattleScene
- **Intent**: Tactical isometric combat.
- **Lifecycle Methods**:
  - [x] `OnAttach`: Logging implemented.
  - [x] `OnDetach`: Logging implemented.
  - [ ] `OnUpdate`: Stub.
  - [ ] `OnRender`: Stub.
  - [ ] `OnInput`: Stub.
- **Features**:
  - [ ] Isometric grid rendering.
  - [ ] Combatant turn logic.
  - [ ] Action/Ability execution.

### MenuScene
- **Intent**: In-game pause/inventory menu.
- **Lifecycle Methods**:
  - [x] `OnAttach`: Logging implemented.
  - [x] `OnDetach`: Logging implemented.
  - [ ] `OnUpdate`: Stub.
  - [ ] `OnRender`: Stub.
  - [ ] `OnInput`: Stub.
- **Features**:
  - [ ] Overlay rendering.
  - [ ] Inventory/Settings management.

## Recommendations for Next Steps
1. **Scene Navigation**: Implement the logic to transition from `MainMenuScene` to `StartRunScene` and then to `OverworldScene`.
2. **UI Framework**: Integrate or implement a basic UI rendering system (potentially using ImGui if supported by the engine) to handle buttons and menus.
3. **Data Models**: Define the data structures for Characters, Items, and Enemies to be used across `BattleScene` and `OverworldScene`.
4. **Isometric Rendering**: Start implementing the isometric coordinate system and grid rendering in `BattleScene`.
