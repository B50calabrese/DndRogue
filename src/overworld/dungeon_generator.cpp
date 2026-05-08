#include "overworld/dungeon_generator.h"
#include <random>

namespace dnd_rogue::overworld {

DungeonGenerator::DungeonGenerator(int width, int height, unsigned int seed)
    : width_(width), height_(height), seed_(seed) {}

MapData DungeonGenerator::Generate() {
  MapData map;
  map.width = width_;
  map.height = height_;
  map.tiles.resize(width_ * height_, TileType::kWall);

  std::mt19937 gen(seed_ == 0 ? std::random_device{}() : seed_);
  std::uniform_int_distribution<> dis_x(1, width_ - 2);
  std::uniform_int_distribution<> dis_y(1, height_ - 2);

  // Simple random walk generator
  int x = dis_x(gen);
  int y = dis_y(gen);
  int tiles_to_dig = (width_ * height_) / 3;

  while (tiles_to_dig > 0) {
    if (map.GetTile(x, y) == TileType::kWall) {
      map.SetTile(x, y, TileType::kFloor);
      tiles_to_dig--;
    }

    int dir = std::uniform_int_distribution<>(0, 3)(gen);
    if (dir == 0 && x < width_ - 2) x++;
    else if (dir == 1 && x > 1) x--;
    else if (dir == 2 && y < height_ - 2) y++;
    else if (dir == 3 && y > 1) y--;
  }

  // Add some NPCs and enemies
  int entities_to_place = 10;
  while (entities_to_place > 0) {
    int nx = dis_x(gen);
    int ny = dis_y(gen);
    if (map.GetTile(nx, ny) == TileType::kFloor) {
      EntityType type = (entities_to_place % 2 == 0) ? EntityType::kNPC : EntityType::kEnemy;
      map.entities.push_back({type, {nx, ny}});
      entities_to_place--;
    }
  }

  return map;
}

}  // namespace dnd_rogue::overworld
