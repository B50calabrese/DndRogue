#ifndef DND_ROGUE_SCENES_BATTLE_SCENE_H_
#define DND_ROGUE_SCENES_BATTLE_SCENE_H_

#include <engine/scene/scene.h>

namespace dnd_rogue::scenes {

/**
 * @brief Scene for isometric combat encounters.
 *
 * This scene handles the tactical, turn-based battle logic in an
 * isometric perspective.
 */
class BattleScene : public engine::Scene {
 public:
  BattleScene();
  ~BattleScene() override = default;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float delta_time_seconds) override;
  void OnRender() override;
  bool OnInput() override;
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_BATTLE_SCENE_H_
