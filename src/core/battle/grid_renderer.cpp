#include "core/battle/grid_renderer.h"
#include <engine/graphics/primitive_renderer.h>

namespace dnd_rogue::core::battle {

void GridRenderer::Render(int grid_width, int grid_height, float tile_width, float tile_height, const glm::mat4& view_projection) {
  engine::graphics::PrimitiveRenderer::StartBatch(view_projection);

  glm::vec4 line_color = {0.8f, 0.8f, 0.8f, 1.0f};

  for (int y = 0; y <= grid_height; ++y) {
    glm::vec2 start = WorldToIsometric(0, (float)y, tile_width, tile_height);
    glm::vec2 end = WorldToIsometric((float)grid_width, (float)y, tile_width, tile_height);
    engine::graphics::PrimitiveRenderer::SubmitLine(start, end, line_color);
  }

  for (int x = 0; x <= grid_width; ++x) {
    glm::vec2 start = WorldToIsometric((float)x, 0, tile_width, tile_height);
    glm::vec2 end = WorldToIsometric((float)x, (float)grid_height, tile_width, tile_height);
    engine::graphics::PrimitiveRenderer::SubmitLine(start, end, line_color);
  }

  engine::graphics::PrimitiveRenderer::FinalizeBatch();
  engine::graphics::PrimitiveRenderer::RenderBatch();
}

glm::vec2 GridRenderer::WorldToIsometric(float x, float y, float tile_width, float tile_height) {
  return {
    (x - y) * (tile_width / 2.0f),
    (x + y) * (tile_height / 2.0f)
  };
}

} // namespace dnd_rogue::core::battle
