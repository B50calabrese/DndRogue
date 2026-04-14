#include "scenes/overworld_scene.h"

#include <iostream>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/util/logger.h"
#include "engine/core/engine.h"
#include "engine/graphics/primitive_renderer.h"
#include "engine/input/input_manager.h"
#include "core/overworld/room_generator.h"

namespace dnd_rogue::scenes {

OverworldScene::OverworldScene() : engine::Scene("OverworldScene") {}

void OverworldScene::OnAttach() {
  LOG_INFO("OverworldScene: Attached");

  // Initialize Map
  core::overworld::RoomGenerator generator;
  map_data_ = generator.Generate(map_config_);

  // Initialize Camera
  auto& win = engine::Engine::window();
  float screen_width = static_cast<float>(win.width());
  float screen_height = static_cast<float>(win.height());

  camera_ = std::make_unique<engine::graphics::Camera>(
      0.0f, screen_width, screen_height, 0.0f); // Top-left (0,0)

  UpdateCamera();
}

void OverworldScene::OnDetach() {
  LOG_INFO("OverworldScene: Detached");
}

void OverworldScene::OnUpdate(float delta_time_seconds) {
  // Logic for map navigation and event triggers.
}

void OverworldScene::OnRender() {
  if (!map_data_ || !camera_) return;

  engine::graphics::PrimitiveRenderer::StartBatch(camera_->view_projection_matrix());

  float tile_size = map_config_.tile_size;
  float line_thickness = map_config_.grid_line_thickness;

  // 1. Render Tiles
  for (int y = 0; y < map_data_->height(); ++y) {
    for (int x = 0; x < map_data_->width(); ++x) {
      glm::vec2 pos = {x * tile_size, y * tile_size};
      glm::vec4 color = core::overworld::GetTileColor(map_data_->GetTile(x, y));

      engine::graphics::PrimitiveRenderer::SubmitQuad(
          pos, {tile_size, tile_size}, color);
    }
  }

  // 2. Render Grid Lines (drawn between tiles)
  glm::vec4 line_color = {0.0f, 0.0f, 0.0f, 1.0f}; // Black

  // Vertical lines
  for (int x = 0; x <= map_data_->width(); ++x) {
    float x_pos = x * tile_size;
    engine::graphics::PrimitiveRenderer::SubmitLine(
        {x_pos, 0}, {x_pos, map_data_->height() * tile_size}, line_color, line_thickness);
  }
  // Horizontal lines
  for (int y = 0; y <= map_data_->height(); ++y) {
    float y_pos = y * tile_size;
    engine::graphics::PrimitiveRenderer::SubmitLine(
        {0, y_pos}, {map_data_->width() * tile_size, y_pos}, line_color, line_thickness);
  }

  // 3. Render Player (Green placeholder)
  glm::ivec2 p_pos = map_data_->player_pos();
  engine::graphics::PrimitiveRenderer::SubmitQuad(
      {p_pos.x * tile_size, p_pos.y * tile_size},
      {tile_size, tile_size},
      core::overworld::GetTileColor(core::overworld::TileType::kPlayer));

  engine::graphics::PrimitiveRenderer::FinalizeBatch();
  engine::graphics::PrimitiveRenderer::RenderBatch();

  // 4. Render UI Divider (White line)
  // The UI is not part of the world, so we use a screen-space projection or just a separate batch
  // For simplicity, let's draw it in a separate batch with identity/screen projection if possible,
  // or just use the same camera but fixed position if it doesn't move.
  // Actually, UI usually shouldn't move with the camera.

  auto& win = engine::Engine::window();
  float screen_width = static_cast<float>(win.width());
  float screen_height = static_cast<float>(win.height());

  // Create a screen-space projection for UI
  glm::mat4 screen_proj = glm::ortho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);
  engine::graphics::PrimitiveRenderer::StartBatch(screen_proj);

  float divider_x = screen_width * 0.9f; // 10% from the right
  engine::graphics::PrimitiveRenderer::SubmitLine(
      {divider_x, 0}, {divider_x, screen_height}, {1.0f, 1.0f, 1.0f, 1.0f}, 2.0f);

  engine::graphics::PrimitiveRenderer::FinalizeBatch();
  engine::graphics::PrimitiveRenderer::RenderBatch();
}

bool OverworldScene::OnInput() {
  auto& input = engine::InputManager::Get();

  if (input.IsKeyPressed(engine::KeyCode::kW) || input.IsKeyPressed(engine::KeyCode::kUp)) {
    HandleMovement(0, -1);
    return true;
  }
  if (input.IsKeyPressed(engine::KeyCode::kS) || input.IsKeyPressed(engine::KeyCode::kDown)) {
    HandleMovement(0, 1);
    return true;
  }
  if (input.IsKeyPressed(engine::KeyCode::kA) || input.IsKeyPressed(engine::KeyCode::kLeft)) {
    HandleMovement(-1, 0);
    return true;
  }
  if (input.IsKeyPressed(engine::KeyCode::kD) || input.IsKeyPressed(engine::KeyCode::kRight)) {
    HandleMovement(1, 0);
    return true;
  }

  return false;
}

void OverworldScene::HandleMovement(int dx, int dy) {
  glm::ivec2 new_pos = map_data_->player_pos() + glm::ivec2(dx, dy);

  if (map_data_->IsWalkable(new_pos.x, new_pos.y)) {
    map_data_->set_player_pos(new_pos);

    // Check for other tile interactions (TODOs)
    core::overworld::TileType target_tile = map_data_->GetTile(new_pos.x, new_pos.y);
    if (target_tile == core::overworld::TileType::kEnemy) {
      // TODO: Trigger battle
    } else if (target_tile == core::overworld::TileType::kPortal) {
      // TODO: Next floor
    } else if (target_tile == core::overworld::TileType::kChest) {
      // TODO: Open chest
    }

    UpdateCamera();
  }
}

void OverworldScene::UpdateCamera() {
  if (!camera_ || !map_data_) return;

  auto& win = engine::Engine::window();
  float screen_width = static_cast<float>(win.width());
  float screen_height = static_cast<float>(win.height());

  // Drawable area for the map (90% width)
  float drawable_width = screen_width * 0.9f;
  float drawable_height = screen_height;

  float tile_size = map_config_.tile_size;
  glm::ivec2 p_pos = map_data_->player_pos();

  // Target: player centered in drawable area
  float target_x = (p_pos.x + 0.5f) * tile_size - drawable_width * 0.5f;
  float target_y = (p_pos.y + 0.5f) * tile_size - drawable_height * 0.5f;

  // Clamp camera so it doesn't go past map edges
  float max_camera_x = std::max(0.0f, map_data_->width() * tile_size - drawable_width);
  float max_camera_y = std::max(0.0f, map_data_->height() * tile_size - drawable_height);

  target_x = std::clamp(target_x, 0.0f, max_camera_x);
  target_y = std::clamp(target_y, 0.0f, max_camera_y);

  camera_->set_position({target_x, target_y, 0.0f});
}

}  // namespace dnd_rogue::scenes
