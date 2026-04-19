#ifndef DND_ROGUE_SCENES_BATTLE_SCENE_H_
#define DND_ROGUE_SCENES_BATTLE_SCENE_H_

#include <engine/scene/scene.h>
#include <engine/graphics/camera.h>
#include <memory>
#include <vector>

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

 private:
  void CreateUI();
  void UpdateLayout();
  glm::vec2 WorldToIsometric(float x, float y) const;
  void ClampCamera();

  // Grid configuration
  int grid_width_ = 20;
  int grid_height_ = 20;
  float tile_width_ = 64.0f;
  float tile_height_ = 32.0f; // 2:1 aspect ratio

  std::unique_ptr<engine::graphics::Camera> camera_;

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
