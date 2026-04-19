#include "scenes/battle_scene.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/core/engine.h"
#include "engine/ecs/components/quad.h"
#include "engine/ecs/components/text.h"
#include "engine/graphics/primitive_renderer.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/text_renderer.h"
#include "engine/input/input_manager.h"
#include "engine/ui/ui_components.h"
#include "engine/util/logger.h"

namespace dnd_rogue::scenes {

BattleScene::BattleScene() : engine::Scene("BattleScene") {}

void BattleScene::OnAttach() {
  LOG_INFO("BattleScene: Attached");

  auto& win = engine::Engine::window();
  last_window_width_ = static_cast<float>(win.width());
  last_window_height_ = static_cast<float>(win.height());

  camera_ = std::make_unique<engine::graphics::Camera>(
      0.0f, last_window_width_, last_window_height_, 0.0f);

  engine::graphics::TextRenderer::Get().LoadFont(
      "battle_font", "fonts/menu_font.ttf", 24);
  engine::graphics::TextRenderer::Get().LoadFont(
      "small_battle_font", "fonts/menu_font.ttf", 14);

  CreateUI();

  // Center camera on grid
  glm::vec2 center_iso = WorldToIsometric(grid_width_ / 2.0f, grid_height_ / 2.0f);
  camera_->set_position({center_iso.x - last_window_width_ / 2.0f,
                         center_iso.y - last_window_height_ / 2.0f, 0.0f});

  ClampCamera();
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

  auto& input = engine::InputManager::Get();
  float cam_speed = 500.0f * delta_time_seconds;
  glm::vec3 cam_pos = camera_->position();

  if (input.IsKeyDown(engine::KeyCode::kW)) cam_pos.y -= cam_speed;
  if (input.IsKeyDown(engine::KeyCode::kS)) cam_pos.y += cam_speed;
  if (input.IsKeyDown(engine::KeyCode::kA)) cam_pos.x -= cam_speed;
  if (input.IsKeyDown(engine::KeyCode::kD)) cam_pos.x += cam_speed;

  camera_->set_position(cam_pos);
  ClampCamera();
}

void BattleScene::OnRender() {
  if (!camera_) return;

  engine::graphics::PrimitiveRenderer::StartBatch(camera_->view_projection_matrix());

  glm::vec4 line_color = {0.8f, 0.8f, 0.8f, 1.0f};

  // Render grid lines
  for (int y = 0; y <= grid_height_; ++y) {
    glm::vec2 start = WorldToIsometric(0, (float)y);
    glm::vec2 end = WorldToIsometric((float)grid_width_, (float)y);
    engine::graphics::PrimitiveRenderer::SubmitLine(start, end, line_color);
  }

  for (int x = 0; x <= grid_width_; ++x) {
    glm::vec2 start = WorldToIsometric((float)x, 0);
    glm::vec2 end = WorldToIsometric((float)x, (float)grid_height_);
    engine::graphics::PrimitiveRenderer::SubmitLine(start, end, line_color);
  }

  engine::graphics::PrimitiveRenderer::FinalizeBatch();
  engine::graphics::PrimitiveRenderer::RenderBatch();
}

bool BattleScene::OnInput() {
  return false;
}

void BattleScene::CreateUI() {
  // Status Bar
  status_bar_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(status_bar_, engine::ui::UITransform{});
  registry_.AddComponent<engine::ecs::components::Quad>(
      status_bar_, engine::ecs::components::Quad{{0.5f, 0.5f, 0.5f, 1.0f}});

  auto status_text = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(status_text, engine::ui::UITransform{});
  registry_.AddComponent<engine::ecs::components::Text>(
      status_text, engine::ecs::components::Text{"Status Bar", "battle_font", 1.0f, {1, 1, 1, 1}});
  registry_.AddComponent<engine::ui::UIHierarchy>(status_text, engine::ui::UIHierarchy{status_bar_});
  registry_.AddComponent<engine::ui::UIHierarchy>(status_bar_, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, {status_text}});

  // Command Bar
  command_bar_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(command_bar_, engine::ui::UITransform{});
  registry_.AddComponent<engine::ecs::components::Quad>(
      command_bar_, engine::ecs::components::Quad{{0.3f, 0.3f, 0.3f, 1.0f}});

  std::vector<engine::ecs::EntityID> slots;
  for (int i = 0; i < 20; ++i) {
    auto slot = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(slot, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        slot, engine::ecs::components::Quad{{0.4f, 0.4f, 0.4f, 1.0f}});

    auto slot_text = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(slot_text, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Text>(
        slot_text, engine::ecs::components::Text{std::to_string(i + 1), "small_battle_font", 0.8f, {1, 1, 1, 1}});

    registry_.AddComponent<engine::ui::UIHierarchy>(slot_text, engine::ui::UIHierarchy{slot});
    registry_.AddComponent<engine::ui::UIHierarchy>(slot, engine::ui::UIHierarchy{command_bar_, {slot_text}});
    slots.push_back(slot);
  }
  registry_.AddComponent<engine::ui::UIHierarchy>(command_bar_, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, slots});

  // Portraits
  portraits_container_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(portraits_container_, engine::ui::UITransform{});

  portrait_entities_.clear();
  for (int i = 0; i < 4; ++i) {
    auto portrait = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(portrait, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        portrait, engine::ecs::components::Quad{{0.2f, 0.2f, 0.2f, 1.0f}});

    auto hb_bg = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(hb_bg, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        hb_bg, engine::ecs::components::Quad{{1.0f, 0.0f, 0.0f, 1.0f}});

    auto hb_fill = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(hb_fill, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        hb_fill, engine::ecs::components::Quad{{0.0f, 1.0f, 0.0f, 1.0f}});

    registry_.AddComponent<engine::ui::UIHierarchy>(hb_bg, engine::ui::UIHierarchy{portrait});
    registry_.AddComponent<engine::ui::UIHierarchy>(hb_fill, engine::ui::UIHierarchy{portrait});
    registry_.AddComponent<engine::ui::UIHierarchy>(portrait, engine::ui::UIHierarchy{portraits_container_, {hb_bg, hb_fill}});
    portrait_entities_.push_back(portrait);
  }
  registry_.AddComponent<engine::ui::UIHierarchy>(portraits_container_, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, portrait_entities_});

  UpdateLayout();
}

void BattleScene::UpdateLayout() {
  auto& win = engine::Engine::window();
  last_window_width_ = static_cast<float>(win.width());
  last_window_height_ = static_cast<float>(win.height());

  float sw = last_window_width_;
  float sh = last_window_height_;

  if (camera_) {
    camera_->set_projection(0.0f, sw, sh, 0.0f);
  }

  float sb_h = sh * 0.1f;
  auto& sb_t = registry_.GetComponent<engine::ui::UITransform>(status_bar_);
  sb_t.local_pos = {0, 0};
  sb_t.size = {sw, sb_h};
  sb_t.z_index = 150;

  auto& sb_hie = registry_.GetComponent<engine::ui::UIHierarchy>(status_bar_);
  auto& sb_text_t = registry_.GetComponent<engine::ui::UITransform>(sb_hie.children[0]);
  sb_text_t.local_pos = {sw * 0.5f, sb_h * 0.5f};

  float cb_h = sh * 0.1f;
  auto& cb_t = registry_.GetComponent<engine::ui::UITransform>(command_bar_);
  cb_t.local_pos = {0, sh - cb_h};
  cb_t.size = {sw, cb_h};
  cb_t.z_index = 150;

  auto& cb_hie = registry_.GetComponent<engine::ui::UIHierarchy>(command_bar_);
  float slot_w = sw / 10.0f;
  float slot_h = cb_h / 2.0f;
  for (int i = 0; i < 20; ++i) {
    auto slot_ent = cb_hie.children[i];
    auto& slot_t = registry_.GetComponent<engine::ui::UITransform>(slot_ent);
    int row = i / 10;
    int col = i % 10;
    slot_t.local_pos = {col * slot_w + 2.0f, row * slot_h + 2.0f};
    slot_t.size = {slot_w - 4.0f, slot_h - 4.0f};

    auto& slot_hie = registry_.GetComponent<engine::ui::UIHierarchy>(slot_ent);
    auto& slot_text_t = registry_.GetComponent<engine::ui::UITransform>(slot_hie.children[0]);
    slot_text_t.local_pos = {slot_t.size.x * 0.5f, slot_t.size.y * 0.5f};
  }

  float p_area_h = sh - sb_h - cb_h;
  float p_w = sw * 0.1f;
  auto& pc_t = registry_.GetComponent<engine::ui::UITransform>(portraits_container_);
  pc_t.local_pos = {0, sb_h};
  pc_t.size = {p_w, p_area_h};

  float p_h = p_area_h / 4.0f;
  for (int i = 0; i < 4; ++i) {
    auto p_ent = portrait_entities_[i];
    auto& p_t = registry_.GetComponent<engine::ui::UITransform>(p_ent);
    p_t.local_pos = {5.0f, i * p_h + 5.0f};
    p_t.size = {p_w - 10.0f, p_h - 10.0f};

    auto& p_hie = registry_.GetComponent<engine::ui::UIHierarchy>(p_ent);
    float hb_h = 10.0f;
    auto& hb_bg_t = registry_.GetComponent<engine::ui::UITransform>(p_hie.children[0]);
    hb_bg_t.local_pos = {0, p_t.size.y - hb_h};
    hb_bg_t.size = {p_t.size.x, hb_h};

    auto& hb_fill_t = registry_.GetComponent<engine::ui::UITransform>(p_hie.children[1]);
    hb_fill_t.local_pos = {0, p_t.size.y - hb_h};
    hb_fill_t.size = {p_t.size.x * 0.8f, hb_h};
  }
}

glm::vec2 BattleScene::WorldToIsometric(float x, float y) const {
  return {
    (x - y) * (tile_width_ / 2.0f),
    (x + y) * (tile_height_ / 2.0f)
  };
}

void BattleScene::ClampCamera() {
  float min_x = -grid_height_ * (tile_width_ / 2.0f);
  float max_x = grid_width_ * (tile_width_ / 2.0f);
  float min_y = 0.0f;
  float max_y = (grid_width_ + grid_height_) * (tile_height_ / 2.0f);

  glm::vec3 pos = camera_->position();

  if (max_x - min_x > last_window_width_) {
    pos.x = std::clamp(pos.x, min_x, max_x - last_window_width_);
  } else {
    pos.x = (min_x + max_x - last_window_width_) / 2.0f;
  }

  if (max_y - min_y > last_window_height_) {
    pos.y = std::clamp(pos.y, min_y, max_y - last_window_height_);
  } else {
    pos.y = (min_y + max_y - last_window_height_) / 2.0f;
  }

  camera_->set_position(pos);
}

}  // namespace dnd_rogue::scenes
