#ifndef DND_ROGUE_SCENES_BATTLE_SCENE_H_
#define DND_ROGUE_SCENES_BATTLE_SCENE_H_

#include <engine/scene/scene.h>
#include "scenes/overworld_scene.h"

namespace dnd_rogue::scenes {

/**
 * @brief Skeleton for the Battle scene.
 */
class BattleScene : public engine::Scene {
 public:
  BattleScene();
  explicit BattleScene(const OverworldState& state);
  ~BattleScene() override = default;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float delta_time_seconds) override;
  void OnRender() override;
  bool OnInput() override;

 private:
  OverworldState state_;
  float timer_ = 0.0f;
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_BATTLE_SCENE_H_
