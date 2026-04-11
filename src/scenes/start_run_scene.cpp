#include "scenes/start_run_scene.h"

#include <iostream>
#include "engine/util/logger.h"

namespace dnd_rogue::scenes {

StartRunScene::StartRunScene() : engine::Scene("StartRunScene") {}

void StartRunScene::OnAttach() {
  LOG_INFO("StartRunScene: Attached");
}

void StartRunScene::OnDetach() {
  LOG_INFO("StartRunScene: Detached");
}

void StartRunScene::OnUpdate(float delta_time_seconds) {
  // Logic for character selection and run options.
}

void StartRunScene::OnRender() {
  // Render character options, selection UI.
}

bool StartRunScene::OnInput() {
  // Handle character/option selection input.
  return false;
}

}  // namespace dnd_rogue::scenes
