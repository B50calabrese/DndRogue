#include "scenes/battle_scene.h"

#include "core/constants.h"
#include "engine/graphics/renderer.h"
#include "engine/scene/scene_manager.h"
#include "engine/util/logger.h"

namespace dnd_rogue::scenes {

BattleScene::BattleScene() : engine::Scene("BattleScene") {}

BattleScene::BattleScene(const OverworldState& state)
    : engine::Scene("BattleScene"), state_(state) {}

void BattleScene::OnAttach() {
  LOG_INFO("BattleScene: Attached");
  timer_ = 0.0f;
}

void BattleScene::OnDetach() {
  LOG_INFO("BattleScene: Detached");
}

void BattleScene::OnUpdate(float delta_time_seconds) {
  timer_ += delta_time_seconds;
  if (timer_ >= 2.0f) {
    engine::SceneManager::Get().SetScene(
        std::make_unique<OverworldScene>(state_));
  }
}

void BattleScene::OnRender() {
  auto& renderer = engine::graphics::Renderer::Get();
  auto camera = engine::graphics::Camera(
      0, static_cast<float>(dnd_rogue::core::kWindowWidth), 0,
      static_cast<float>(dnd_rogue::core::kWindowHeight));

  renderer.BeginFrame(camera);

  renderer.DrawText("default", "Battling",
                    {dnd_rogue::core::kWindowWidth / 2.0f - 100.0f,
                     dnd_rogue::core::kWindowHeight / 2.0f},
                    0.0f, 2.0f, {1.0f, 1.0f, 1.0f, 1.0f});

  renderer.EndFrame();
}

bool BattleScene::OnInput() {
  return false;
}

}  // namespace dnd_rogue::scenes
