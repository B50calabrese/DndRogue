#include "core/math_utils.h"

namespace dnd_rogue::core {

glm::vec2 ScreenToWorld(const glm::vec2& screen_pos,
                        const engine::graphics::Camera& camera,
                        int window_width, int window_height) {
  // 1. Normalize screen coordinates to [-1, 1] (Normalized Device Coordinates)
  // GLFW mouse coordinates are (0,0) at top-left.
  // Engine/OpenGL defaults to (0,0) at bottom-left for screen to world mapping here,
  // but let's be careful.
  float x = (2.0f * screen_pos.x) / static_cast<float>(window_width) - 1.0f;
  float y = 1.0f - (2.0f * screen_pos.y) / static_cast<float>(window_height);

  // 2. Create NDC position
  glm::vec4 ndc_pos(x, y, 0.0f, 1.0f);

  // 3. Transform by inverse view-projection matrix
  glm::mat4 inv_vp = glm::inverse(camera.view_projection_matrix());
  glm::vec4 world_pos = inv_vp * ndc_pos;

  return glm::vec2(world_pos.x, world_pos.y);
}

}  // namespace dnd_rogue::core
