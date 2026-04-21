#include "scenes/battle_scene.h"

#include <algorithm>
#include "engine/core/engine.h"
#include "engine/graphics/text_renderer.h"
#include "engine/util/logger.h"
#include "core/battle/grid_renderer.h"

namespace dnd_rogue::scenes {

BattleScene::BattleScene() : engine::Scene("BattleScene") {}

void BattleScene::OnAttach() {
  LOG_INFO("BattleScene: Attached");

  auto& win = engine::Engine::window();
  last_window_width_ = static_cast<float>(win.width());
  last_window_height_ = static_cast<float>(win.height());

  camera_manager_ = std::make_unique<core::battle::BattleCamera>(last_window_width_, last_window_height_);

  engine::graphics::TextRenderer::Get().LoadFont(
      "battle_font", "fonts/menu_font.ttf", 24);
  engine::graphics::TextRenderer::Get().LoadFont(
      "small_battle_font", "fonts/menu_font.ttf", 14);

  ui_manager_ = std::make_unique<core::battle::BattleUIManager>(registry_);

  // Initial Layout
  UpdateLayout();

  // Center camera on grid
  float center_x = (grid_width_ - grid_height_) * (tile_width_ / 4.0f);
  float center_y = (grid_width_ + grid_height_) * (tile_height_ / 4.0f);
  camera_manager_->SetPosition({center_x - last_window_width_ / 2.0f,
                                center_y - last_window_height_ / 2.0f, 0.0f});
}

void BattleScene::OnDetach() {
  LOG_INFO("BattleScene: Detached");
}

void BattleScene::OnUpdate(float delta_time_seconds) {
  auto& win = engine::Engine::window();
  if (static_cast<float>(win.width()) != last_window_width_ ||
      static_cast<float>(win.height()) != last_window_height_) {
    UpdateLayout();
  }

  camera_manager_->Update(delta_time_seconds, (float)grid_width_, (float)grid_height_, tile_width_, tile_height_);
}

void BattleScene::OnRender() {
  if (!camera_manager_) return;

  core::battle::GridRenderer::Render(grid_width_, grid_height_, tile_width_, tile_height_, camera_manager_->GetViewProjection());
}

bool BattleScene::OnInput() {
  return false;
}

void BattleScene::UpdateLayout() {
  auto& win = engine::Engine::window();
  last_window_width_ = static_cast<float>(win.width());
  last_window_height_ = static_cast<float>(win.height());

  if (camera_manager_) {
    camera_manager_->Resize(last_window_width_, last_window_height_);
  }

  if (ui_manager_) {
    core::battle::BattleUIManager::LayoutInfo info;
    info.screen_width = last_window_width_;
    info.screen_height = last_window_height_;
    info.status_bar_height = info.screen_height * 0.1f;
    info.command_bar_height = info.screen_height * 0.1f;
    info.portrait_area_height = info.screen_height - info.status_bar_height - info.command_bar_height;
    info.portrait_width = info.screen_width * 0.1f;

    ui_manager_->UpdateLayout(info);
  }
}

}  // namespace dnd_rogue::scenes
