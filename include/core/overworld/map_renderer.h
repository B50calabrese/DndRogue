#ifndef DND_ROGUE_CORE_OVERWORLD_MAP_RENDERER_H_
#define DND_ROGUE_CORE_OVERWORLD_MAP_RENDERER_H_

#include <glm/glm.hpp>
#include "core/overworld/map_data.h"
#include "core/overworld/map_config.h"

namespace dnd_rogue::core::overworld {

/**
 * @brief Handles rendering of the overworld map.
 */
class MapRenderer {
 public:
  /**
   * @brief Renders the map and player using placeholder colors.
   *
   * This can be extended or subclassed in the future to support sprite-based rendering.
   *
   * @param map The map data to render.
   * @param config The map configuration.
   * @param view_projection The view-projection matrix for the current camera.
   */
  void Render(const MapData& map, const MapConfig& config, const glm::mat4& view_projection);

 private:
  void RenderTiles(const MapData& map, float tile_size);
  void RenderGridLines(const MapData& map, float tile_size, float thickness);
  void RenderPlayer(const glm::ivec2& player_pos, float tile_size);
};

}  // namespace dnd_rogue::core::overworld

#endif  // DND_ROGUE_CORE_OVERWORLD_MAP_RENDERER_H_
