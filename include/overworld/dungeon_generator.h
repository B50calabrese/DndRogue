#ifndef DND_ROGUE_OVERWORLD_DUNGEON_GENERATOR_H_
#define DND_ROGUE_OVERWORLD_DUNGEON_GENERATOR_H_

#include "overworld/map_generator.h"

namespace dnd_rogue::overworld {

class DungeonGenerator : public IMapGenerator {
 public:
  DungeonGenerator(int width, int height, unsigned int seed = 0);
  MapData Generate() override;

 private:
  int width_;
  int height_;
  unsigned int seed_;
};

}  // namespace dnd_rogue::overworld

#endif  // DND_ROGUE_OVERWORLD_DUNGEON_GENERATOR_H_
