#include "scenes/main_menu_scene.h"

#include <iostream>
#include "engine/util/logger.h"

namespace dnd_rogue::scenes {

MainMenuScene::MainMenuScene() : engine::Scene("MainMenuScene") {}

void MainMenuScene::OnAttach() {
  LOG_INFO("MainMenuScene: Attached");
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
