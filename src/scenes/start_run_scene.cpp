#include "scenes/start_run_scene.h"

#include <iostream>
#include <memory>
#include <vector>

#include "core/session.h"
#include "core/ui_utils.h"
#include "engine/core/engine.h"
#include "engine/ecs/components/quad.h"
#include "engine/ecs/components/text.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/text_renderer.h"
#include "engine/scene/scene_manager.h"
#include "engine/ui/ui_components.h"
#include "engine/util/logger.h"
#include "scenes/overworld_scene.h"

namespace dnd_rogue::scenes {

StartRunScene::StartRunScene() : engine::Scene("StartRunScene") {
  for (int i = 0; i < 4; ++i) {
    selected_classes_[i] = core::models::CharacterClass::Fighter;
  }
}

void StartRunScene::OnAttach() {
  LOG_INFO("StartRunScene: Attached");

  engine::graphics::TextRenderer::Get().LoadFont(
      "menu_font", "fonts/menu_font.ttf", 24);
  engine::graphics::TextRenderer::Get().LoadFont(
      "small_font", "fonts/menu_font.ttf", 16);

  CreateUI();
}

void StartRunScene::OnDetach() { LOG_INFO("StartRunScene: Detached"); }

void StartRunScene::OnUpdate(float delta_time_seconds) {}

void StartRunScene::OnRender() {}

bool StartRunScene::OnInput() { return false; }

void StartRunScene::CreateUI() {
  auto& win = engine::Engine::window();
  float screen_width = static_cast<float>(win.width());
  float screen_height = static_cast<float>(win.height());

  // Background
  auto background = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      background,
      engine::ui::UITransform{{0, 0}, {screen_width, screen_height}});
  registry_.AddComponent<engine::ecs::components::Quad>(
      background,
      engine::ecs::components::Quad{{0.05f, 0.05f, 0.05f, 1.0f}, {0, 0}, 0.0f});

  float section_width = screen_width * 0.25f;
  float section_height = screen_height * 0.8f;
  float section_y = (screen_height - section_height) * 0.5f;

  for (int i = 0; i < 4; ++i) {
    float section_x = i * section_width;

    // Class Square
    float square_size = section_width * 0.6f;
    float square_x = section_x + (section_width - square_size) * 0.5f;
    float square_y = section_y + 50.0f;  // Near top

    auto square_entity = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(
        square_entity, engine::ui::UITransform{{square_x, square_y},
                                               {square_size, square_size}});
    registry_.AddComponent<engine::ecs::components::Quad>(
        square_entity,
        engine::ecs::components::Quad{
            core::models::GetCharacterClassColor(selected_classes_[i]),
            {0, 0},
            1.0f});

    // Interaction for square to show picker
    registry_.AddComponent<engine::ui::UIInteractable>(
        square_entity, engine::ui::UIInteractable{
                           false, false, [this, i]() { ShowPicker(i); }});
    class_squares_[i] = square_entity;

    // Class Text
    auto text_entity = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(
        text_entity, engine::ui::UITransform{
                         {square_size * 0.5f, square_size * 0.5f}, {0, 0}});
    registry_.AddComponent<engine::ecs::components::Text>(
        text_entity,
        engine::ecs::components::Text{
            core::models::GetCharacterClassName(selected_classes_[i]),
            "menu_font",
            0.8f,
            {1, 1, 1, 1},
            2.0f});

    registry_.AddComponent<engine::ui::UIHierarchy>(
        square_entity,
        engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, {text_entity}});
    registry_.AddComponent<engine::ui::UIHierarchy>(
        text_entity, engine::ui::UIHierarchy{square_entity});

    class_texts_[i] = text_entity;
  }

  // Start Run Button
  float btn_w = 200.0f;
  float btn_h = 50.0f;
  core::UIUtils::CreateButton(
      registry_, {(screen_width - btn_w) * 0.5f, 20.0f}, {btn_w, btn_h},
      "Start Run", "menu_font", kGreenColor, kGreenColor * 1.2f, {1, 1, 1, 1},
      {1, 1, 1, 1}, [this]() {
        std::vector<core::models::CharacterClass> classes;
        for (auto cls : selected_classes_) classes.push_back(cls);
        core::Session::Get().InitRun(classes);
        engine::SceneManager::Get().SetScene(
            std::make_unique<OverworldScene>());
      });
}

void StartRunScene::ShowPicker(int index) {
  if (active_picker_index_ == index) {
    HidePicker();
    return;
  }
  HidePicker();
  active_picker_index_ = index;

  auto& win = engine::Engine::window();
  float screen_width = static_cast<float>(win.width());
  float screen_height = static_cast<float>(win.height());

  // Invisible full-screen "click-out" detector for picker
  click_out_overlay_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      click_out_overlay_,
      engine::ui::UITransform{{0, 0}, {screen_width, screen_height}});
  // Use a z-index between the background and the picker
  registry_.GetComponent<engine::ui::UITransform>(click_out_overlay_).z_index =
      140;
  registry_.AddComponent<engine::ui::UIInteractable>(
      click_out_overlay_,
      engine::ui::UIInteractable{false, false, [this]() { HidePicker(); }});

  float section_width = screen_width * 0.25f;
  float section_height = screen_height * 0.8f;
  float section_y = (screen_height - section_height) * 0.5f;

  float square_size = section_width * 0.6f;
  float square_y = section_y + 50.0f;

  float picker_y = square_y + square_size + 10.0f;
  float picker_width = section_width;
  float picker_height = 150.0f;  // Approx height for 3 rows

  picker_container_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      picker_container_,
      engine::ui::UITransform{{index * section_width, picker_y},
                              {picker_width, picker_height}});
  registry_.GetComponent<engine::ui::UITransform>(picker_container_).z_index =
      150;
  registry_.AddComponent<engine::ecs::components::Quad>(
      picker_container_,
      engine::ecs::components::Quad{kPickerBackgroundColor, {0, 0}, 5.0f});

  float item_w = picker_width / 4.0f;
  float item_h = picker_height / 3.0f;

  std::vector<engine::ecs::EntityID> children;

  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 4; ++col) {
      int cls_idx = row * 4 + col;
      auto cls = static_cast<core::models::CharacterClass>(cls_idx);

      auto item_entity = registry_.CreateEntity();
      registry_.AddComponent<engine::ui::UITransform>(
          item_entity, engine::ui::UITransform{{col * item_w, row * item_h},
                                               {item_w, item_h}});
      registry_.AddComponent<engine::ecs::components::Quad>(
          item_entity,
          engine::ecs::components::Quad{
              core::models::GetCharacterClassColor(cls), {0.1f, 0.1f}, 6.0f});

      auto item_text = registry_.CreateEntity();
      registry_.AddComponent<engine::ui::UITransform>(
          item_text,
          engine::ui::UITransform{{item_w * 0.5f, item_h * 0.5f}, {0, 0}});
      registry_.AddComponent<engine::ecs::components::Text>(
          item_text, engine::ecs::components::Text{
                         core::models::GetCharacterClassName(cls),
                         "small_font",
                         0.5f,
                         {1, 1, 1, 1},
                         7.0f});

      registry_.AddComponent<engine::ui::UIHierarchy>(
          item_entity, engine::ui::UIHierarchy{picker_container_, {item_text}});
      registry_.AddComponent<engine::ui::UIHierarchy>(
          item_text, engine::ui::UIHierarchy{item_entity});

      registry_.AddComponent<engine::ui::UIInteractable>(
          item_entity,
          engine::ui::UIInteractable{false, false, [this, index, cls]() {
                                       selected_classes_[index] = cls;
                                       UpdateCharacterUI(index);
                                       HidePicker();
                                     }});

      children.push_back(item_entity);
    }
  }

  registry_.AddComponent<engine::ui::UIHierarchy>(
      picker_container_,
      engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, children});
}

void StartRunScene::HidePicker() {
  if (picker_container_ != engine::ecs::INVALID_ENTITY) {
    DestroyEntityRecursive(picker_container_);
    picker_container_ = engine::ecs::INVALID_ENTITY;
  }
  if (click_out_overlay_ != engine::ecs::INVALID_ENTITY) {
    registry_.DeleteEntity(click_out_overlay_);
    click_out_overlay_ = engine::ecs::INVALID_ENTITY;
  }
  active_picker_index_ = -1;
}

void StartRunScene::DestroyEntityRecursive(engine::ecs::EntityID entity) {
  if (registry_.HasComponent<engine::ui::UIHierarchy>(entity)) {
    auto& hier = registry_.GetComponent<engine::ui::UIHierarchy>(entity);
    // Make a copy of children because registry_.DeleteEntity might affect the
    // original vector
    std::vector<engine::ecs::EntityID> children = hier.children;
    for (auto child : children) {
      DestroyEntityRecursive(child);
    }
  }
  registry_.DeleteEntity(entity);
}

void StartRunScene::UpdateCharacterUI(int index) {
  auto cls = selected_classes_[index];
  if (registry_.HasComponent<engine::ecs::components::Quad>(
          class_squares_[index])) {
    registry_.GetComponent<engine::ecs::components::Quad>(class_squares_[index])
        .color = core::models::GetCharacterClassColor(cls);
  }
  if (registry_.HasComponent<engine::ecs::components::Text>(
          class_texts_[index])) {
    registry_.GetComponent<engine::ecs::components::Text>(class_texts_[index])
        .content = core::models::GetCharacterClassName(cls);
  }
}

}  // namespace dnd_rogue::scenes
