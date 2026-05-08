# Project Status

This file tracks the current progress and infrastructure of the project.

## Most Recent Changes
- Reverted codebase to a basic skeleton.
- Removed game-specific logic (D&D/Roguelike elements).
- Kept scene structure: MainMenuScene, OverworldScene, BattleScene, MenuScene.
- Updated MainMenuScene to transition directly to OverworldScene.
- Kept `UIUtils` as a generic utility.

## Current State of Infrastructure

### Core Application
- **Lifecycle**: Functional skeleton in `DndRogueApp`.
- **Scene Management**: Starts in `MainMenuScene`.

### GameEngine Integration
- **Submodule**: Integrated and configured.

### Scenes
- **MainMenuScene**: Functional with basic UI (Start Run, Exit). Transitions to `OverworldScene`.
- **OverworldScene**: Fully functional implementation of exploration mode.
    - Tile-based rendering (16x16 pixels scaled by 3x).
    - Grid-based A* pathfinding for mouse-click movement.
    - Smooth character interpolation.
    - Centered camera with map boundary clamping.
    - Support for Hub world (loaded from text file) and Procedural Dungeons.
    - Separate entity storage (NPCs and Enemies) in `MapData`.
    - Collision detection with enemies triggers `BattleScene` transition.
    - State serialization for seamless return from other scenes.
- **BattleScene**: Functional placeholder.
    - Displays "Battling" for 2 seconds.
    - Transitions back to `OverworldScene` with state preservation.
- **MenuScene**: Skeleton stub.
