#include "scenes/menu_scene.h"

#include <iostream>
#include "engine/util/logger.h"

namespace dnd_rogue::scenes {

MenuScene::MenuScene() : engine::Scene("MenuScene") {}

void MenuScene::OnAttach() {
  LOG_INFO("MenuScene: Attached");
}

void MenuScene::OnDetach() {
  LOG_INFO("MenuScene: Detached");
}

void MenuScene::OnUpdate(float delta_time_seconds) {
  // Logic for handling in-game menu options.
}

void MenuScene::OnRender() {
  // Render the pause menu overlay.
}

bool MenuScene::OnInput() {
  // Handle menu navigation while paused.
  return false;
}

}  // namespace dnd_rogue::scenes
