# DndRogue

A D&D-inspired roguelike game built using a custom C++ game engine.

## Prerequisites

- C++20 compatible compiler
- CMake 3.15 or higher
- GLFW 3.3
- OpenGL
- FreeType 2.x

## Building the Game

### 1. Initialize Submodules
```bash
git submodule update --init --recursive
```

### 2. Configure the Build
```bash
cmake -B build
```

### 3. Build the Application
```bash
cmake --build build --target DndRogue -j$(nproc)
```

The executable will be located in `build/DndRogue`.

## Testing

The project uses GoogleTest for unit testing. To build and run the tests:

### Configure with testing enabled
```bash
cmake -B build -DBUILD_GAME_TESTS=ON
```

### Build all tests
```bash
cmake --build build -j$(nproc)
```

### Running Tests
Individual test binaries are located in `build/tests/`. You can run them manually or use `ctest` from the build directory:
```bash
cd build && ctest
```

## Project Structure

- `src/`: Source files (`.cpp`)
- `include/`: Header files (`.h`)
- `assets/`: Game assets (textures, fonts, etc.)
- `tests/`: Unit tests
- `GameEngine/`: Submodule containing the game engine
