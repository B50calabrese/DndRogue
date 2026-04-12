#include "scenes/main_menu_scene.h"

#include <iostream>
#include <memory>

#include "engine/core/engine.h"
#include "engine/ecs/components/quad.h"
#include "engine/ecs/components/text.h"
#include "engine/graphics/renderer.h"
#include "engine/graphics/text_renderer.h"
#include "engine/scene/scene_manager.h"
#include "engine/ui/ui_components.h"
#include "engine/util/logger.h"
#include "scenes/start_run_scene.h"

namespace dnd_rogue::scenes {

MainMenuScene::MainMenuScene() : engine::Scene("MainMenuScene") {}

void MainMenuScene::OnAttach() {
  LOG_INFO("MainMenuScene: Attached");

  // Load font
  engine::graphics::TextRenderer::Get().LoadFont(
      "menu_font", "assets/fonts/menu_font.ttf", 24);

  auto& win = engine::Engine::window();
  float screen_width = static_cast<float>(win.width());
  float screen_height = static_cast<float>(win.height());

  // 1. Background
  auto background = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      background, engine::ui::UITransform{{0, 0}, {screen_width, screen_height}});
  registry_.AddComponent<engine::ecs::components::Quad>(
      background, engine::ecs::components::Quad{kBackgroundColor, {0, 0}, 0.0f});

  // Button dimensions
  glm::vec2 button_size = {screen_width * kButtonWidthPercent,
                           screen_height * kButtonHeightPercent};
  float button_x = (screen_width - button_size.x) * 0.5f;

  // 2. Start Run Button
  auto start_border = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      start_border,
      engine::ui::UITransform{{button_x - 2, screen_height * 2.0f / 3.0f - 2},
                              {button_size.x + 4, button_size.y + 4}});
  registry_.AddComponent<engine::ecs::components::Quad>(
      start_border,
      engine::ecs::components::Quad{kButtonBorderColor, {0, 0}, 0.5f});

  auto start_button = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      start_button,
      engine::ui::UITransform{{button_x, screen_height * 2.0f / 3.0f},
                              button_size});
  registry_.AddComponent<engine::ecs::components::Quad>(
      start_button,
      engine::ecs::components::Quad{kButtonInteriorColor, {0, 0}, 1.0f});
  registry_.AddComponent<engine::ui::UIInteractable>(
      start_button,
      engine::ui::UIInteractable{
          false, false,
          []() {
            engine::SceneManager::Get().SetScene(
                std::make_unique<StartRunScene>());
          },
          [this, start_button](bool hovered) {
            if (registry_.HasComponent<engine::ecs::components::Quad>(
                    start_button)) {
              auto& quad =
                  registry_.GetComponent<engine::ecs::components::Quad>(
                      start_button);
              quad.color = hovered ? MainMenuScene::kButtonHoverColor
                                   : MainMenuScene::kButtonInteriorColor;
            }
          }});

  auto start_text = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      start_text,
      engine::ui::UITransform{{button_size.x * 0.5f, button_size.y * 0.5f},
                              {0, 0}});
  registry_.AddComponent<engine::ui::UIHierarchy>(
      start_text, engine::ui::UIHierarchy{start_button});
  registry_.AddComponent<engine::ecs::components::Text>(
      start_text,
      engine::ecs::components::Text{"Start run", "menu_font", 1.0f, kTextColor,
                                   2.0f});

  // 3. Exit Button
  auto exit_border = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      exit_border,
      engine::ui::UITransform{{button_x - 2, screen_height * 1.0f / 3.0f - 2},
                              {button_size.x + 4, button_size.y + 4}});
  registry_.AddComponent<engine::ecs::components::Quad>(
      exit_border,
      engine::ecs::components::Quad{kButtonBorderColor, {0, 0}, 0.5f});

  auto exit_button = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      exit_button,
      engine::ui::UITransform{{button_x, screen_height * 1.0f / 3.0f},
                              button_size});
  registry_.AddComponent<engine::ecs::components::Quad>(
      exit_button,
      engine::ecs::components::Quad{kButtonInteriorColor, {0, 0}, 1.0f});
  registry_.AddComponent<engine::ui::UIInteractable>(
      exit_button,
      engine::ui::UIInteractable{
          false, false,
          []() { engine::Engine::Shutdown(); },
          [this, exit_button](bool hovered) {
            if (registry_.HasComponent<engine::ecs::components::Quad>(
                    exit_button)) {
              auto& quad = registry_.GetComponent<engine::ecs::components::Quad>(
                  exit_button);
              quad.color = hovered ? MainMenuScene::kButtonHoverColor
                                   : MainMenuScene::kButtonInteriorColor;
            }
          }});

  auto exit_text = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(
      exit_text,
      engine::ui::UITransform{{button_size.x * 0.5f, button_size.y * 0.5f},
                              {0, 0}});
  registry_.AddComponent<engine::ui::UIHierarchy>(
      exit_text, engine::ui::UIHierarchy{exit_button});
  registry_.AddComponent<engine::ecs::components::Text>(
      exit_text,
      engine::ecs::components::Text{"Exit", "menu_font", 1.0f, kTextColor,
                                   2.0f});

  // Update hierarchy for buttons to have their texts
  registry_.AddComponent<engine::ui::UIHierarchy>(
      start_button, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, {start_text}});

  registry_.AddComponent<engine::ui::UIHierarchy>(
      exit_button, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, {exit_text}});
}

void MainMenuScene::OnDetach() {
  LOG_INFO("MainMenuScene: Detached");
}

void MainMenuScene::OnUpdate(float delta_time_seconds) {
  // Logic for handling menu selections, etc.
}

void MainMenuScene::OnRender() {
  // Render buttons and background for the main menu.
}

bool MainMenuScene::OnInput() {
  // Handle menu navigation input.
  return false;
}

}  // namespace dnd_rogue::scenes
