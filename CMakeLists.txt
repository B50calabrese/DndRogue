cmake_minimum_required(VERSION 3.15)
project(DndRogue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. ADD THE ENGINE SUBDIRECTORY
# This makes the "GameEngine" target available to your game.
add_subdirectory("GameEngine")

# 2. SOURCE AND HEADER SETUP
set(SOURCE_FILES
    "src/dnd_rogue_app.cpp"
    "src/core/ui_utils.cpp"
    "src/scenes/battle_scene.cpp"
    "src/scenes/main_menu_scene.cpp"
    "src/scenes/menu_scene.cpp"
    "src/scenes/overworld_scene.cpp"
    "src/scenes/start_run_scene.cpp"
)

# Headers
file(GLOB_RECURSE INCLUDE_FILES "include/*.h" "src/*.h")

# 3. ASSET INFORMATION
set(ASSET_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSET_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

# Copy assets to build directory for relative path loading
if(EXISTS "${ASSET_SOURCE_DIR}")
    file(COPY "${ASSET_SOURCE_DIR}/" DESTINATION "${ASSET_BUILD_DIR}")
endif()

# 4. CREATE A LIBRARY FOR REUSABLE GAME LOGIC
# This is a good practice to separate game logic from the main entry point
add_library(DndRogueLibrary STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

# Inject the asset path as a macro for C++ code
target_compile_definitions(DndRogueLibrary PUBLIC
    ENGINE_ASSETS_PATH=\"${ASSET_BUILD_DIR}/\"
)

# Link the Engine to the Library
target_link_libraries(DndRogueLibrary PUBLIC GameEngine)

# Ensure the game's include folder is PUBLIC so anyone linking to it sees it
target_include_directories(DndRogueLibrary PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# 5. CREATE THE MAIN EXECUTABLE
add_executable(DndRogue "src/main.cpp")
target_link_libraries(DndRogue PRIVATE DndRogueLibrary)

# 6. VISUAL STUDIO SETTINGS
set_target_properties(DndRogue PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

# 7. TESTING
option(BUILD_GAME_TESTS "Build game tests" ON)
if(BUILD_GAME_TESTS)
    enable_testing()

    # Note: Google Test targets (gtest, gtest_main) are provided by
    # the GameEngine subdirectory.

    # Helper to add a game test
    function(add_game_test TEST_NAME SOURCE_FILES)
        add_executable(${TEST_NAME} ${SOURCE_FILES})
        target_link_libraries(${TEST_NAME} PRIVATE DndRogueLibrary gtest_main)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

        # Set a consistent output directory for tests
        set_target_properties(${TEST_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests"
        )

        # Set working directory for tests so they can find assets if needed
        set_target_properties(${TEST_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endfunction()

    # Automatically discover and add tests from tests/
    file(GLOB_RECURSE GAME_TEST_SOURCES "tests/*_test.cpp")
    foreach(TEST_SOURCE ${GAME_TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
        add_game_test(${TEST_NAME} ${TEST_SOURCE})
    endforeach()
endif()
