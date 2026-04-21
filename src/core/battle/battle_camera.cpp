#include "core/battle/battle_camera.h"
#include <engine/input/input_manager.h>
#include <algorithm>

namespace dnd_rogue::core::battle {

BattleCamera::BattleCamera(float width, float height)
    : viewport_width_(width), viewport_height_(height) {
  camera_ = std::make_unique<engine::graphics::Camera>(0.0f, width, height, 0.0f);
}

void BattleCamera::Update(float delta_time, float grid_width, float grid_height, float tile_width, float tile_height) {
  auto& input = engine::InputManager::Get();
  float cam_speed = 500.0f * delta_time;
  glm::vec3 cam_pos = camera_->position();

  if (input.IsKeyDown(engine::KeyCode::kW)) cam_pos.y -= cam_speed;
  if (input.IsKeyDown(engine::KeyCode::kS)) cam_pos.y += cam_speed;
  if (input.IsKeyDown(engine::KeyCode::kA)) cam_pos.x -= cam_speed;
  if (input.IsKeyDown(engine::KeyCode::kD)) cam_pos.x += cam_speed;

  camera_->set_position(cam_pos);
  Clamp(grid_width, grid_height, tile_width, tile_height);
}

void BattleCamera::Resize(float width, float height) {
  viewport_width_ = width;
  viewport_height_ = height;
  camera_->set_projection(0.0f, width, height, 0.0f);
}

void BattleCamera::SetPosition(const glm::vec3& pos) {
  camera_->set_position(pos);
}

void BattleCamera::Clamp(float grid_width, float grid_height, float tile_width, float tile_height) {
  float min_x = -grid_height * (tile_width / 2.0f);
  float max_x = grid_width * (tile_width / 2.0f);
  float min_y = 0.0f;
  float max_y = (grid_width + grid_height) * (tile_height / 2.0f);

  glm::vec3 pos = camera_->position();

  if (max_x - min_x > viewport_width_) {
    pos.x = std::clamp(pos.x, min_x, max_x - viewport_width_);
  } else {
    pos.x = (min_x + max_x - viewport_width_) / 2.0f;
  }

  if (max_y - min_y > viewport_height_) {
    pos.y = std::clamp(pos.y, min_y, max_y - viewport_height_);
  } else {
    pos.y = (min_y + max_y - viewport_height_) / 2.0f;
  }

  camera_->set_position(pos);
}

} // namespace dnd_rogue::core::battle
