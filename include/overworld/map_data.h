#ifndef DND_ROGUE_OVERWORLD_MAP_DATA_H_
#define DND_ROGUE_OVERWORLD_MAP_DATA_H_

#include <vector>
#include <glm/vec2.hpp>

namespace dnd_rogue::overworld {

enum class TileType {
  kFloor,
  kWall,
  kNpcPlaceholder
};

struct MapData {
  int width = 0;
  int height = 0;
  std::vector<TileType> tiles;

  TileType GetTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
      return TileType::kWall;
    }
    return tiles[y * width + x];
  }

  void SetTile(int x, int y, TileType type) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
      tiles[y * width + x] = type;
    }
  }

  bool IsWalkable(int x, int y) const {
    return GetTile(x, y) != TileType::kWall;
  }
};

}  // namespace dnd_rogue::overworld

#endif  // DND_ROGUE_OVERWORLD_MAP_DATA_H_
