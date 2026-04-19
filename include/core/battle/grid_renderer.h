#ifndef DND_ROGUE_CORE_BATTLE_GRID_RENDERER_H_
#define DND_ROGUE_CORE_BATTLE_GRID_RENDERER_H_

#include <glm/glm.hpp>

namespace dnd_rogue::core::battle {

class GridRenderer {
 public:
  static void Render(int grid_width, int grid_height, float tile_width, float tile_height, const glm::mat4& view_projection);
 private:
  static glm::vec2 WorldToIsometric(float x, float y, float tile_width, float tile_height);
};

} // namespace dnd_rogue::core::battle

#endif // DND_ROGUE_CORE_BATTLE_GRID_RENDERER_H_
