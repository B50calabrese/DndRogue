#ifndef DND_ROGUE_OVERWORLD_HUB_GENERATOR_H_
#define DND_ROGUE_OVERWORLD_HUB_GENERATOR_H_

#include <string>
#include "overworld/map_generator.h"

namespace dnd_rogue::overworld {

class HubGenerator : public IMapGenerator {
 public:
  explicit HubGenerator(const std::string& filepath);
  MapData Generate() override;

 private:
  std::string filepath_;
};

}  // namespace dnd_rogue::overworld

#endif  // DND_ROGUE_OVERWORLD_HUB_GENERATOR_H_
