#include "scenes/overworld_scene.h"

#include <iostream>
#include "engine/util/logger.h"

namespace dnd_rogue::scenes {

OverworldScene::OverworldScene() : engine::Scene("OverworldScene") {}

void OverworldScene::OnAttach() {
  LOG_INFO("OverworldScene: Attached");
}

void OverworldScene::OnDetach() {
  LOG_INFO("OverworldScene: Detached");
}

void OverworldScene::OnUpdate(float delta_time_seconds) {
  // Logic for map navigation and event triggers.
}

void OverworldScene::OnRender() {
  // Render the roguelike map and player.
}

bool OverworldScene::OnInput() {
  // Handle map movement and interaction input.
  return false;
}

}  // namespace dnd_rogue::scenes
