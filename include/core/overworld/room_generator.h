#ifndef DND_ROGUE_CORE_OVERWORLD_ROOM_GENERATOR_H_
#define DND_ROGUE_CORE_OVERWORLD_ROOM_GENERATOR_H_

#include "core/overworld/map_generator.h"

namespace dnd_rogue::core::overworld {

/**
 * @brief Generates a map with interconnected rooms.
 */
class RoomGenerator : public MapGenerator {
 public:
  std::unique_ptr<MapData> Generate(const MapConfig& config) override;

 private:
  struct Room {
    int x, y, w, h;
    glm::ivec2 Center() const { return {x + w / 2, y + h / 2}; }
    bool Intersects(const Room& other) const {
      return (x <= other.x + other.w && x + w >= other.x &&
              y <= other.y + other.h && y + h >= other.y);
    }
  };

  void ApplyRoomToMap(MapData& map, const Room& room);
  void ApplyHorizontalTunnel(MapData& map, int x1, int x2, int y);
  void ApplyVerticalTunnel(MapData& map, int y1, int y2, int x);
};

}  // namespace dnd_rogue::core::overworld

#endif  // DND_ROGUE_CORE_OVERWORLD_ROOM_GENERATOR_H_
