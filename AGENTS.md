# AI Agent Guidance

Welcome, AI agent! This file provides guidance on how to contribute to this repository.

## Project Status and Progress
- **Status File**: Current progress and infrastructure details are tracked in [STATUS.md](STATUS.md).
- **Mandatory Update**: As the final step of any task, you **must** update [STATUS.md](STATUS.md) with your changes.

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

- **GameEngine**: The core engine functionality is located in the `GameEngine/` submodule. Do not modify the engine code unless necessary.
- **Library**: Most game logic should reside in a library target defined in `CMakeLists.txt` to facilitate testing.
- **Lifecycle**: The main application subclasses `engine::Application`. Use `OnInit`, `OnUpdate`, and `OnShutdown` for lifecycle management.

## Testing

- **GoogleTest**: We use GoogleTest for unit testing.
- **Test Placement**: New tests should be placed in the `tests/` directory and follow the `*_test.cpp` naming convention.
- **Verification**: Always run existing tests before submitting changes to ensure no regressions were introduced.

## Assets

- Assets should be placed in the `assets/` directory.
- The build system copies assets to the build directory so they can be loaded using relative paths.
- Use the `ENGINE_ASSETS_PATH` macro in C++ code to reference the asset directory.

## Scenes

The following scene skeletons are available:

- **MainMenuScene**: The entry point of the game.
- **OverworldScene**: Intended for exploration or a main game hub.
- **BattleScene**: Intended for specialized encounters or combat.
- **MenuScene**: An in-game/pause menu.
