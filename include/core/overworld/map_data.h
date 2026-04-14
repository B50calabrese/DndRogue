#ifndef DND_ROGUE_CORE_OVERWORLD_MAP_DATA_H_
#define DND_ROGUE_CORE_OVERWORLD_MAP_DATA_H_

#include <vector>
#include <glm/glm.hpp>
#include "core/overworld/tile_type.h"

namespace dnd_rogue::core::overworld {

/**
 * @brief Holds the grid data and player state for an overworld map.
 */
class MapData {
 public:
  /**
   * @brief Constructs a new MapData object.
   * @param width The width of the grid in tiles.
   * @param height The height of the grid in tiles.
   */
  MapData(int width, int height)
      : width_(width), height_(height), tiles_(width * height, TileType::kNone) {}

  /**
   * @brief Gets the tile type at the specified coordinates.
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @return The TileType at the given position, or TileType::kNone if out of bounds.
   */
  TileType GetTile(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return TileType::kNone;
    return tiles_[y * width_ + x];
  }

  /**
   * @brief Sets the tile type at the specified coordinates.
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @param type The TileType to set.
   */
  void SetTile(int x, int y, TileType type) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
      tiles_[y * width_ + x] = type;
    }
  }

  /**
   * @brief Returns the width of the map in tiles.
   */
  int width() const { return width_; }

  /**
   * @brief Returns the height of the map in tiles.
   */
  int height() const { return height_; }

  /**
   * @brief Returns the player's current grid position.
   */
  const glm::ivec2& player_pos() const { return player_pos_; }

  /**
   * @brief Sets the player's grid position.
   */
  void set_player_pos(const glm::ivec2& pos) { player_pos_ = pos; }

  /**
   * @brief Checks if a tile is walkable by the player.
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @return True if the tile is floor or contains an interactable object, false if it's a wall or empty.
   */
  bool IsWalkable(int x, int y) const {
    TileType type = GetTile(x, y);
    return type != TileType::kWall && type != TileType::kNone;
  }

 private:
  int width_;
  int height_;
  std::vector<TileType> tiles_;
  glm::ivec2 player_pos_ = {0, 0};
};

}  // namespace dnd_rogue::core::overworld

#endif  // DND_ROGUE_CORE_OVERWORLD_MAP_DATA_H_
