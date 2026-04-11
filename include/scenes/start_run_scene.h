#ifndef DND_ROGUE_SCENES_START_RUN_SCENE_H_
#define DND_ROGUE_SCENES_START_RUN_SCENE_H_

#include <engine/scene/scene.h>

namespace dnd_rogue::scenes {

/**
 * @brief Scene for starting a new run.
 *
 * This scene allows the player to select their character, difficulty,
 * or other run-specific options before entering the overworld.
 */
class StartRunScene : public engine::Scene {
 public:
  StartRunScene();
  ~StartRunScene() override = default;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float delta_time_seconds) override;
  void OnRender() override;
  bool OnInput() override;
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_START_RUN_SCENE_H_
