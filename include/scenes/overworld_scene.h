#ifndef DND_ROGUE_SCENES_OVERWORLD_SCENE_H_
#define DND_ROGUE_SCENES_OVERWORLD_SCENE_H_

#include <engine/scene/scene.h>
#include <engine/graphics/camera.h>
#include "core/overworld/map_data.h"
#include "core/overworld/map_config.h"

namespace dnd_rogue::scenes {

/**
 * @brief Scene for the roguelike overworld.
 *
 * This scene manages the exploration part of the game, where the player
 * navigates through the map and encounters events or battles.
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

 private:
  void UpdateCamera();
  void HandleMovement(int dx, int dy);

  core::overworld::MapConfig map_config_;
  std::unique_ptr<core::overworld::MapData> map_data_;
  std::unique_ptr<engine::graphics::Camera> camera_;
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_OVERWORLD_SCENE_H_
