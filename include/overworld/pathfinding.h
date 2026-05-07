#ifndef DND_ROGUE_OVERWORLD_PATHFINDING_H_
#define DND_ROGUE_OVERWORLD_PATHFINDING_H_

#include <vector>
#include <glm/vec2.hpp>
#include "overworld/map_data.h"

namespace dnd_rogue::overworld {

/**
 * @brief Finds the shortest path between two points on the map using A*.
 *
 * @param start Starting tile coordinates.
 * @param end Goal tile coordinates.
 * @param map The map data.
 * @return A vector of tile coordinates representing the path, or empty if no path found.
 */
std::vector<glm::ivec2> FindPath(const glm::ivec2& start, const glm::ivec2& end,
                                const MapData& map);

}  // namespace dnd_rogue::overworld

#endif  // DND_ROGUE_OVERWORLD_PATHFINDING_H_
