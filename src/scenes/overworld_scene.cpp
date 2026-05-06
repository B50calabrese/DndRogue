#include "scenes/overworld_scene.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

#include "core/constants.h"
#include "core/math_utils.h"
#include "engine/core/application.h"
#include "engine/graphics/renderer.h"
#include "engine/input/input_manager.h"
#include "engine/util/logger.h"
#include "overworld/dungeon_generator.h"
#include "overworld/hub_generator.h"
#include "overworld/pathfinding.h"

namespace dnd_rogue::scenes {

using namespace dnd_rogue::core;
using namespace dnd_rogue::overworld;

OverworldScene::OverworldScene() : engine::Scene("OverworldScene") {
  camera_ = std::make_unique<engine::graphics::Camera>(
      0, static_cast<float>(kWindowWidth), 0,
      static_cast<float>(kWindowHeight));
}

void OverworldScene::OnAttach() {
  LOG_INFO("OverworldScene: Attached");
  LoadMap(std::make_unique<HubGenerator>(
      engine::graphics::Renderer::Get().ResolveAssetPath("maps/hub.txt")));
}

void OverworldScene::OnDetach() {
  LOG_INFO("OverworldScene: Detached");
}

void OverworldScene::LoadMap(std::unique_ptr<IMapGenerator> generator) {
  map_data_ = generator->Generate();
  // Place player at first floor tile found, or (1,1)
  bool found = false;
  for (int y = 0; y < map_data_.height; ++y) {
    for (int x = 0; x < map_data_.width; ++x) {
      if (map_data_.GetTile(x, y) == TileType::kFloor) {
        player_pos_ =
            glm::vec2(x * kScaledTileSize + kScaledTileSize * 0.5f,
                      y * kScaledTileSize + kScaledTileSize * 0.5f);
        found = true;
        break;
      }
    }
    if (found) break;
  }
  if (!found) {
    player_pos_ = glm::vec2(kScaledTileSize * 1.5f, kScaledTileSize * 1.5f);
  }
  current_path_.clear();
}

void OverworldScene::OnUpdate(float delta_time_seconds) {
  HandleMovement(delta_time_seconds);
  UpdateCamera(delta_time_seconds);
}

void OverworldScene::HandleMovement(float delta_time) {
  if (path_index_ >= current_path_.size()) return;

  glm::ivec2 target_tile = current_path_[path_index_];
  glm::vec2 target_pos =
      glm::vec2(target_tile.x * kScaledTileSize + kScaledTileSize * 0.5f,
                target_tile.y * kScaledTileSize + kScaledTileSize * 0.5f);

  float dist = glm::distance(player_pos_, target_pos);
  float move_dist = kPlayerSpeed * delta_time;

  if (move_dist >= dist) {
    player_pos_ = target_pos;
    path_index_++;
  } else {
    player_pos_ += glm::normalize(target_pos - player_pos_) * move_dist;
  }
}

void OverworldScene::UpdateCamera(float delta_time) {
  // Center camera on player
  glm::vec3 cam_pos = camera_->position();

  // Target position is player_pos but we need to account for window size
  float window_w = static_cast<float>(kWindowWidth);
  float window_h = static_cast<float>(kWindowHeight);

  float target_x = player_pos_.x - window_w * 0.5f;
  float target_y = player_pos_.y - window_h * 0.5f;

  // Clamp camera to map bounds
  float map_w = map_data_.width * kScaledTileSize;
  float map_h = map_data_.height * kScaledTileSize;

  float min_x = 0.0f;
  float max_x = std::max(0.0f, map_w - window_w);
  float min_y = 0.0f;
  float max_y = std::max(0.0f, map_h - window_h);

  cam_pos.x = std::clamp(target_x, min_x, max_x);
  cam_pos.y = std::clamp(target_y, min_y, max_y);

  camera_->set_position(cam_pos);
}

void OverworldScene::OnRender() {
  engine::graphics::Renderer::Get().BeginFrame(*camera_);
  RenderMap();
  RenderPlayer();
  engine::graphics::Renderer::Get().EndFrame();
}

void OverworldScene::RenderMap() {
  auto& renderer = engine::graphics::Renderer::Get();

  for (int y = 0; y < map_data_.height; ++y) {
    for (int x = 0; x < map_data_.width; ++x) {
      TileType type = map_data_.GetTile(x, y);
      glm::vec4 outer_color = kColorFloor;
      glm::vec4 inner_color = kColorFloorInner;

      if (type == TileType::kWall) {
        outer_color = kColorWall;
        inner_color = kColorWallInner;
      } else if (type == TileType::kNpcPlaceholder) {
        outer_color = kColorNPC;
        inner_color = kColorNPCInner;
      }

      glm::vec2 pos = glm::vec2(x * kScaledTileSize, y * kScaledTileSize);
      glm::vec2 size = glm::vec2(kScaledTileSize, kScaledTileSize);

      // Outer quad (border)
      renderer.DrawQuad(pos, size, outer_color);

      // Inner quad
      glm::vec2 inner_pos = pos + glm::vec2(kTileOutlineThickness * kTileScale);
      glm::vec2 inner_size =
          size - glm::vec2(kTileOutlineThickness * kTileScale * 2.0f);
      renderer.DrawQuad(inner_pos, inner_size, inner_color);
    }
  }
}

void OverworldScene::RenderPlayer() {
  auto& renderer = engine::graphics::Renderer::Get();
  glm::vec2 size = glm::vec2(kScaledTileSize, kScaledTileSize);
  glm::vec2 pos = player_pos_ - size * 0.5f;

  renderer.DrawQuad(pos, size, kColorPlayer);

  glm::vec2 inner_pos = pos + glm::vec2(kTileOutlineThickness * kTileScale);
  glm::vec2 inner_size = size - glm::vec2(kTileOutlineThickness * kTileScale * 2.0f);
  renderer.DrawQuad(inner_pos, inner_size, kColorPlayerInner);
}

bool OverworldScene::OnInput() {
  auto& input = engine::InputManager::Get();

  if (input.IsKeyPressed(engine::KeyCode::kH)) {
    is_hub_ = true;
    LoadMap(std::make_unique<HubGenerator>(
        engine::graphics::Renderer::Get().ResolveAssetPath("maps/hub.txt")));
    return true;
  }
  if (input.IsKeyPressed(engine::KeyCode::kD)) {
    is_hub_ = false;
    LoadMap(std::make_unique<DungeonGenerator>(30, 30));
    return true;
  }

  if (input.IsKeyPressed(engine::KeyCode::kMouseLeft)) {
    glm::vec2 mouse_pos = input.mouse_screen_pos();
    // Need window dimensions for ScreenToWorld
    glm::vec2 world_click =
        ScreenToWorld(mouse_pos, *camera_, kWindowWidth, kWindowHeight);

    int tile_x = static_cast<int>(std::floor(world_click.x / kScaledTileSize));
    int tile_y = static_cast<int>(std::floor(world_click.y / kScaledTileSize));

    int start_tile_x = static_cast<int>(std::floor(player_pos_.x / kScaledTileSize));
    int start_tile_y = static_cast<int>(std::floor(player_pos_.y / kScaledTileSize));

    current_path_ = FindPath({start_tile_x, start_tile_y}, {tile_x, tile_y}, map_data_);
    path_index_ = 0;
    return true;
  }

  return false;
}

}  // namespace dnd_rogue::scenes
