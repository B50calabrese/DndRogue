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
#include "core/ui_utils.h"

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
  core::UIUtils::CreateButton(
      registry_, {button_x, screen_height * 2.0f / 3.0f}, button_size,
      "Start run", "menu_font", kButtonInteriorColor, kButtonHoverColor,
      kButtonBorderColor, kTextColor, []() {
        engine::SceneManager::Get().SetScene(std::make_unique<StartRunScene>());
      });

  // 3. Exit Button
  core::UIUtils::CreateButton(
      registry_, {button_x, screen_height * 1.0f / 3.0f}, button_size, "Exit",
      "menu_font", kButtonInteriorColor, kButtonHoverColor, kButtonBorderColor,
      kTextColor, []() { engine::Engine::Shutdown(); });
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
