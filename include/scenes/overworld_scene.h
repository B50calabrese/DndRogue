#ifndef DND_ROGUE_SCENES_OVERWORLD_SCENE_H_
#define DND_ROGUE_SCENES_OVERWORLD_SCENE_H_

#include <engine/scene/scene.h>

namespace dnd_rogue::scenes {

/**
 * @brief Skeleton for the Overworld scene.
 */
class OverworldScene : public engine::Scene {
 public:
  OverworldScene();
  ~OverworldScene() override = default;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float delta_time_seconds) override;
  void OnRender() override;
  bool OnInput() override;
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_OVERWORLD_SCENE_H_
