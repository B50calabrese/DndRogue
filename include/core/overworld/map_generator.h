#ifndef DND_ROGUE_CORE_OVERWORLD_MAP_GENERATOR_H_
#define DND_ROGUE_CORE_OVERWORLD_MAP_GENERATOR_H_

#include <memory>
#include "core/overworld/map_data.h"
#include "core/overworld/map_config.h"

namespace dnd_rogue::core::overworld {

/**
 * @brief Interface for overworld map generation strategies.
 */
class MapGenerator {
 public:
  virtual ~MapGenerator() = default;

  /**
   * @brief Generates a map based on the provided configuration.
   * @param config The configuration for the map.
   * @return A unique pointer to the generated MapData.
   */
  virtual std::unique_ptr<MapData> Generate(const MapConfig& config) = 0;
};

}  // namespace dnd_rogue::core::overworld

#endif  // DND_ROGUE_CORE_OVERWORLD_MAP_GENERATOR_H_
