#ifndef DND_ROGUE_OVERWORLD_MAP_GENERATOR_H_
#define DND_ROGUE_OVERWORLD_MAP_GENERATOR_H_

#include <memory>
#include "overworld/map_data.h"

namespace dnd_rogue::overworld {

/**
 * @brief Interface for map generation.
 */
class IMapGenerator {
 public:
  virtual ~IMapGenerator() = default;

  /**
   * @brief Generates a map.
   * @return The generated MapData.
   */
  virtual MapData Generate() = 0;
};

}  // namespace dnd_rogue::overworld

#endif  // DND_ROGUE_OVERWORLD_MAP_GENERATOR_H_
