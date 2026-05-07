#include "overworld/hub_generator.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "engine/util/logger.h"

namespace dnd_rogue::overworld {

HubGenerator::HubGenerator(const std::string& filepath) : filepath_(filepath) {}

MapData HubGenerator::Generate() {
  MapData map;
  std::ifstream file(filepath_);
  if (!file.is_open()) {
    LOG_ERR("Failed to open hub map file: %s", filepath_.c_str());
    // Return a default small map if file fails to load
    map.width = 5;
    map.height = 5;
    map.tiles.resize(25, TileType::kFloor);
    return map;
  }

  std::vector<std::string> lines;
  std::string line;
  int max_width = 0;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    lines.push_back(line);
    max_width = std::max(max_width, static_cast<int>(line.length()));
  }

  map.width = max_width;
  map.height = static_cast<int>(lines.size());
  map.tiles.resize(map.width * map.height, TileType::kWall);

  // We read from top to bottom, but we want y=0 at the bottom for OpenGL
  for (int y = 0; y < map.height; ++y) {
    const std::string& current_line = lines[map.height - 1 - y];
    for (int x = 0; x < static_cast<int>(current_line.length()); ++x) {
      char c = current_line[x];
      TileType type = TileType::kFloor;
      if (c == '#') type = TileType::kWall;
      else if (c == 'N') type = TileType::kNpcPlaceholder;

      map.SetTile(x, y, type);
    }
  }

  return map;
}

}  // namespace dnd_rogue::overworld
