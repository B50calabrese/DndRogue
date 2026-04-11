# AI Agent Guidance for DndRogue

Welcome, AI agent! This file provides guidance on how to contribute to this repository.

## Coding Standards

- **Google C++ Style Guide**: This project follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- **Clang-Format**: A `.clang-format` file is provided in the root directory. Please ensure all C++ code is formatted using it.
- **Naming Conventions**:
  - Files: `snake_case.cpp`, `snake_case.h`
  - Classes: `PascalCase`
  - Methods: `PascalCase`
  - Variables: `snake_case_` (member variables) or `snake_case` (local variables)
- **C++ Version**: We use **C++20**. Use modern C++ features where appropriate.

## Architecture

- **GameEngine**: The core engine functionality is located in the `GameEngine/` submodule. Do not modify the engine code unless necessary for a cross-repo feature or bug fix.
- **DndRogueLibrary**: Most game logic should reside in a library target defined in `CMakeLists.txt` to facilitate testing.
- **Lifecycle**: The main application subclasses `engine::Application`. Use `OnInit`, `OnUpdate`, and `OnShutdown` for lifecycle management.

## Testing

- **GoogleTest**: We use GoogleTest for unit testing.
- **Test Placement**: New tests should be placed in the `tests/` directory and follow the `*_test.cpp` naming convention.
- **Verification**: Always run existing tests before submitting changes to ensure no regressions were introduced.

## Assets

- Assets should be placed in the `assets/` directory.
- The build system copies assets to the build directory so they can be loaded using relative paths.
- Use the `ENGINE_ASSETS_PATH` macro in C++ code to reference the asset directory.

## Scenes and Their Intentions

To maintain consistency and help future agents understand the game's flow, here is an overview of the initial scenes:

- **MainMenuScene**: The entry point of the game. Handles top-level navigation (New Game, Settings, Quit).
- **StartRunScene**: The transition between the main menu and the game. Responsible for character selection, difficulty settings, and other pre-run configurations.
- **OverworldScene**: The primary exploration hub of the roguelike. Manages map navigation, event triggers, and movement between combat encounters.
- **BattleScene**: Handles the isometric combat encounters. This is where tactical, turn-based battle logic resides.
- **MenuScene**: An in-game/pause menu. Intended to be pushed onto the scene stack to allow for inventory management, settings, or pausing without losing current scene state.

Please ensure any new logic related to these areas is implemented in their respective scene classes.
