#ifndef DND_ROGUE_CORE_OVERWORLD_TILE_TYPE_H_
#define DND_ROGUE_CORE_OVERWORLD_TILE_TYPE_H_

#include <glm/glm.hpp>
#include <cstdint>

namespace dnd_rogue::core::overworld {

/**
 * @brief Enumeration of different tile types in the overworld.
 */
enum class TileType {
  kNone,    // Black - Not part of the navigatable map
  kFloor,   // White - Basic floor
  kEnemy,   // Red - Enemy
  kPlayer,  // Green - Player
  kPortal,  // Yellow - Portal
  kChest,   // Orange - Chest
  kWall     // Grey - Wall
};

/**
 * @brief Represents a single tile on the map with additional metadata.
 */
struct Tile {
  TileType type = TileType::kNone;
  uint32_t variant = 0; // Can represent different enemy types, floor textures, etc.
};

/**
 * @brief Helper to get the placeholder color for a tile type.
 */
inline glm::vec4 GetTileColor(TileType type) {
  switch (type) {
    case TileType::kNone:   return {0.0f, 0.0f, 0.0f, 1.0f}; // Black
    case TileType::kFloor:  return {1.0f, 1.0f, 1.0f, 1.0f}; // White
    case TileType::kEnemy:  return {1.0f, 0.0f, 0.0f, 1.0f}; // Red
    case TileType::kPlayer: return {0.0f, 1.0f, 0.0f, 1.0f}; // Green
    case TileType::kPortal: return {1.0f, 1.0f, 0.0f, 1.0f}; // Yellow
    case TileType::kChest:  return {1.0f, 0.5f, 0.0f, 1.0f}; // Orange
    case TileType::kWall:   return {0.5f, 0.5f, 0.5f, 1.0f}; // Grey
    default:                return {0.0f, 0.0f, 0.0f, 1.0f};
  }
}

}  // namespace dnd_rogue::core::overworld

#endif  // DND_ROGUE_CORE_OVERWORLD_TILE_TYPE_H_
