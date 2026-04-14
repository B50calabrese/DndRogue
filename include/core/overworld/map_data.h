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
  MapData(int width, int height)
      : width_(width), height_(height), tiles_(width * height, TileType::kNone) {}

  TileType GetTile(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return TileType::kNone;
    return tiles_[y * width_ + x];
  }

  void SetTile(int x, int y, TileType type) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
      tiles_[y * width_ + x] = type;
    }
  }

  int width() const { return width_; }
  int height() const { return height_; }

  const glm::ivec2& player_pos() const { return player_pos_; }
  void set_player_pos(const glm::ivec2& pos) { player_pos_ = pos; }

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
