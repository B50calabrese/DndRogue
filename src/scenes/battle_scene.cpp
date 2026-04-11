#include "scenes/battle_scene.h"

#include <iostream>
#include "engine/util/logger.h"

namespace dnd_rogue::scenes {

BattleScene::BattleScene() : engine::Scene("BattleScene") {}

void BattleScene::OnAttach() {
  LOG_INFO("BattleScene: Attached");
}

void BattleScene::OnDetach() {
  LOG_INFO("BattleScene: Detached");
}

void BattleScene::OnUpdate(float delta_time_seconds) {
  // Logic for tactical isometric combat.
}

void BattleScene::OnRender() {
  // Render the isometric battle grid and combatants.
}

bool BattleScene::OnInput() {
  // Handle combat unit selection and actions.
  return false;
}

}  // namespace dnd_rogue::scenes
