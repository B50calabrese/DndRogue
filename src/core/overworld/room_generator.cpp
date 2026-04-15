#include "core/overworld/room_generator.h"
#include <algorithm>
#include <random>

namespace dnd_rogue::core::overworld {

std::unique_ptr<MapData> RoomGenerator::Generate(const MapConfig& config) {
  auto map = std::make_unique<MapData>(config.width, config.height);

  // Fill with walls initially
  for (int y = 0; y < config.height; ++y) {
    for (int x = 0; x < config.width; ++x) {
      map->SetTileType(x, y, TileType::kWall);
    }
  }

  std::vector<Room> rooms;
  const int max_rooms = 10;
  const int min_room_size = 3;
  const int max_room_size = 6;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_x(1, config.width - max_room_size - 1);
  std::uniform_int_distribution<> dis_y(1, config.height - max_room_size - 1);
  std::uniform_int_distribution<> dis_size(min_room_size, max_room_size);

  for (int i = 0; i < max_rooms; ++i) {
    int w = dis_size(gen);
    int h = dis_size(gen);
    int x = dis_x(gen);
    int y = dis_y(gen);

    Room new_room{x, y, w, h};
    bool intersects = false;
    for (const auto& other : rooms) {
      if (new_room.Intersects(other)) {
        intersects = true;
        break;
      }
    }

    if (!intersects) {
      ApplyRoomToMap(*map, new_room);

      if (!rooms.empty()) {
        glm::ivec2 prev_center = rooms.back().Center();
        glm::ivec2 new_center = new_room.Center();

        if (std::uniform_int_distribution<>(0, 1)(gen) == 1) {
          ApplyHorizontalTunnel(*map, prev_center.x, new_center.x, prev_center.y);
          ApplyVerticalTunnel(*map, prev_center.y, new_center.y, new_center.x);
        } else {
          ApplyVerticalTunnel(*map, prev_center.y, new_center.y, prev_center.x);
          ApplyHorizontalTunnel(*map, prev_center.x, new_center.x, new_center.y);
        }
      }

      rooms.push_back(new_room);
    }
  }

  // Place Player in the first room
  if (!rooms.empty()) {
    glm::ivec2 start_pos = rooms[0].Center();
    map->set_player_pos(start_pos);
  }

  // Place Portal in the last room
  if (!rooms.empty()) {
    glm::ivec2 portal_pos = rooms.back().Center();
    map->SetTileType(portal_pos.x, portal_pos.y, TileType::kPortal);
  }

  // Place some enemies and chests randomly in floor tiles
  std::uniform_int_distribution<> dis_map_x(0, config.width - 1);
  std::uniform_int_distribution<> dis_map_y(0, config.height - 1);

  int enemies_placed = 0;
  int retry_count = 0;
  while (enemies_placed < 3 && retry_count < 100) {
    int ex = dis_map_x(gen);
    int ey = dis_map_y(gen);
    if (map->GetTile(ex, ey).type == TileType::kFloor && map->player_pos() != glm::ivec2(ex, ey)) {
      map->SetTileType(ex, ey, TileType::kEnemy);
      enemies_placed++;
    }
    retry_count++;
  }

  int chests_placed = 0;
  retry_count = 0;
  while (chests_placed < 2 && retry_count < 100) {
    int cx = dis_map_x(gen);
    int cy = dis_map_y(gen);
    if (map->GetTile(cx, cy).type == TileType::kFloor && map->player_pos() != glm::ivec2(cx, cy)) {
      map->SetTileType(cx, cy, TileType::kChest);
      chests_placed++;
    }
    retry_count++;
  }

  return map;
}

void RoomGenerator::ApplyRoomToMap(MapData& map, const Room& room) {
  for (int y = room.y; y < room.y + room.h; ++y) {
    for (int x = room.x; x < room.x + room.w; ++x) {
      map.SetTileType(x, y, TileType::kFloor);
    }
  }
}

void RoomGenerator::ApplyHorizontalTunnel(MapData& map, int x1, int x2, int y) {
  for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) {
    map.SetTileType(x, y, TileType::kFloor);
  }
}

void RoomGenerator::ApplyVerticalTunnel(MapData& map, int y1, int y2, int x) {
  for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
    map.SetTileType(x, y, TileType::kFloor);
  }
}

}  // namespace dnd_rogue::core::overworld
