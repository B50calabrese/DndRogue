#include "scenes/menu_scene.h"

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
}

void MenuScene::OnRender() {
}

bool MenuScene::OnInput() {
  return false;
}

}  // namespace dnd_rogue::scenes
