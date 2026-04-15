#ifndef DND_ROGUE_CORE_OVERWORLD_MAP_CONFIG_H_
#define DND_ROGUE_CORE_OVERWORLD_MAP_CONFIG_H_

namespace dnd_rogue::core::overworld {

/**
 * @brief Configuration for the overworld map.
 */
struct MapConfig {
  int width = 20;
  int height = 20;
  float tile_size = 64.0f;
  float grid_line_thickness = 2.0f;
};

}  // namespace dnd_rogue::core::overworld

#endif  // DND_ROGUE_CORE_OVERWORLD_MAP_CONFIG_H_
