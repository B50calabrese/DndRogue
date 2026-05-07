#ifndef DND_ROGUE_SCENES_OVERWORLD_SCENE_H_
#define DND_ROGUE_SCENES_OVERWORLD_SCENE_H_

#include <engine/scene/scene.h>
#include <engine/graphics/camera.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "overworld/map_data.h"
#include "overworld/map_generator.h"

namespace dnd_rogue::scenes {

/**
 * @brief Scene for the overworld exploration.
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
  void LoadMap(std::unique_ptr<overworld::IMapGenerator> generator);
  void UpdateCamera(float delta_time);
  void HandleMovement(float delta_time);
  void RenderMap();
  void RenderPlayer();

  overworld::MapData map_data_;
  glm::vec2 player_pos_; // World coordinates
  std::vector<glm::ivec2> current_path_;
  int path_index_ = 0;

  std::unique_ptr<engine::graphics::Camera> camera_;
  bool is_hub_ = true;
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_OVERWORLD_SCENE_H_
