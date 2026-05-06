#ifndef DND_ROGUE_CORE_CONSTANTS_H_
#define DND_ROGUE_CORE_CONSTANTS_H_

#include <glm/vec4.hpp>

namespace dnd_rogue::core {

// Window settings
constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;

// Tile settings
constexpr float kTileSize = 16.0f;
constexpr float kTileScale = 3.0f;
constexpr float kScaledTileSize = kTileSize * kTileScale;

// Rendering settings
constexpr float kTileOutlineThickness = 1.0f;

// Colors
const glm::vec4 kColorFloor = {0.2f, 0.2f, 0.2f, 1.0f};
const glm::vec4 kColorFloorInner = {0.3f, 0.3f, 0.3f, 1.0f};
const glm::vec4 kColorWall = {0.1f, 0.1f, 0.1f, 1.0f};
const glm::vec4 kColorWallInner = {0.4f, 0.4f, 0.4f, 1.0f};
const glm::vec4 kColorPlayer = {0.0f, 0.0f, 0.0f, 1.0f};
const glm::vec4 kColorPlayerInner = {0.0f, 0.8f, 0.0f, 1.0f};
const glm::vec4 kColorNPC = {0.0f, 0.0f, 0.0f, 1.0f};
const glm::vec4 kColorNPCInner = {0.8f, 0.0f, 0.0f, 1.0f};

// Gameplay settings
constexpr float kPlayerSpeed = 200.0f; // pixels per second

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_CONSTANTS_H_
