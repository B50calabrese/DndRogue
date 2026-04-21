#ifndef DND_ROGUE_CORE_BATTLE_BATTLE_CAMERA_H_
#define DND_ROGUE_CORE_BATTLE_BATTLE_CAMERA_H_

#include <engine/graphics/camera.h>
#include <glm/glm.hpp>
#include <memory>

namespace dnd_rogue::core::battle {

class BattleCamera {
 public:
  BattleCamera(float width, float height);

  void Update(float delta_time, float grid_width, float grid_height, float tile_width, float tile_height);
  void Resize(float width, float height);

  const glm::mat4& GetViewProjection() const { return camera_->view_projection_matrix(); }
  const glm::vec3& GetPosition() const { return camera_->position(); }
  void SetPosition(const glm::vec3& pos);

 private:
  void Clamp(float grid_width, float grid_height, float tile_width, float tile_height);

  std::unique_ptr<engine::graphics::Camera> camera_;
  float viewport_width_;
  float viewport_height_;
};

} // namespace dnd_rogue::core::battle

#endif // DND_ROGUE_CORE_BATTLE_BATTLE_CAMERA_H_
