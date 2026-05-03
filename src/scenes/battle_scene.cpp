#include "scenes/battle_scene.h"

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
}

void BattleScene::OnRender() {
}

bool BattleScene::OnInput() {
  return false;
}

}  // namespace dnd_rogue::scenes
