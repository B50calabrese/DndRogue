#include "core/overworld/map_renderer.h"
#include "engine/graphics/primitive_renderer.h"

namespace dnd_rogue::core::overworld {

void MapRenderer::Render(const MapData& map, const MapConfig& config, const glm::mat4& view_projection) {
  engine::graphics::PrimitiveRenderer::StartBatch(view_projection);

  RenderTiles(map, config.tile_size);
  RenderGridLines(map, config.tile_size, config.grid_line_thickness);
  RenderPlayer(map.player_pos(), config.tile_size);

  engine::graphics::PrimitiveRenderer::FinalizeBatch();
  engine::graphics::PrimitiveRenderer::RenderBatch();
}

void MapRenderer::RenderTiles(const MapData& map, float tile_size) {
  for (int y = 0; y < map.height(); ++y) {
    for (int x = 0; x < map.width(); ++x) {
      glm::vec2 pos = {x * tile_size, y * tile_size};
      glm::vec4 color = GetTileColor(map.GetTile(x, y));

      engine::graphics::PrimitiveRenderer::SubmitQuad(
          pos, {tile_size, tile_size}, color);
    }
  }
}

void MapRenderer::RenderGridLines(const MapData& map, float tile_size, float thickness) {
  glm::vec4 line_color = {0.0f, 0.0f, 0.0f, 1.0f}; // Black

  // Vertical lines
  for (int x = 0; x <= map.width(); ++x) {
    float x_pos = x * tile_size;
    engine::graphics::PrimitiveRenderer::SubmitLine(
        {x_pos, 0}, {x_pos, map.height() * tile_size}, line_color, thickness);
  }
  // Horizontal lines
  for (int y = 0; y <= map.height(); ++y) {
    float y_pos = y * tile_size;
    engine::graphics::PrimitiveRenderer::SubmitLine(
        {0, y_pos}, {map.width() * tile_size, y_pos}, line_color, thickness);
  }
}

void MapRenderer::RenderPlayer(const glm::ivec2& player_pos, float tile_size) {
  engine::graphics::PrimitiveRenderer::SubmitQuad(
      {player_pos.x * tile_size, player_pos.y * tile_size},
      {tile_size, tile_size},
      GetTileColor(TileType::kPlayer));
}

}  // namespace dnd_rogue::core::overworld
