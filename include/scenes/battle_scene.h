#ifndef DND_ROGUE_SCENES_BATTLE_SCENE_H_
#define DND_ROGUE_SCENES_BATTLE_SCENE_H_

#include <engine/scene/scene.h>
#include <memory>
#include <vector>
#include "core/battle/battle_camera.h"

namespace dnd_rogue::scenes {

/**
 * @brief Scene for isometric combat encounters.
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

 private:
  void UpdateLayout();

  // Grid configuration
  int grid_width_ = 20;
  int grid_height_ = 20;
  float tile_width_ = 64.0f;
  float tile_height_ = 32.0f;

  std::unique_ptr<core::battle::BattleCamera> camera_manager_;

  // UI Entity IDs
  engine::ecs::EntityID status_bar_ = engine::ecs::INVALID_ENTITY;
  engine::ecs::EntityID command_bar_ = engine::ecs::INVALID_ENTITY;
  engine::ecs::EntityID portraits_container_ = engine::ecs::INVALID_ENTITY;
  std::vector<engine::ecs::EntityID> portrait_entities_;

  float last_window_width_ = 0;
  float last_window_height_ = 0;
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_BATTLE_SCENE_H_
