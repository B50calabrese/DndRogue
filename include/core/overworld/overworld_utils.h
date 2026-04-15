#ifndef DND_ROGUE_CORE_OVERWORLD_OVERWORLD_UTILS_H_
#define DND_ROGUE_CORE_OVERWORLD_OVERWORLD_UTILS_H_

#include <glm/glm.hpp>
#include <algorithm>

namespace dnd_rogue::core::overworld {

/**
 * @brief Utilities for overworld logic.
 */
class OverworldUtils {
 public:
  /**
   * @brief Calculates the camera position to center on a target position while clamping to map boundaries.
   *
   * @param target_pos The target position (usually player) in world coordinates.
   * @param drawable_size The size of the area where the map is drawn (screen minus UI).
   * @param map_size The total size of the map in world coordinates.
   * @return The clamped camera position.
   */
  static glm::vec3 CalculateCameraPosition(
      const glm::vec2& target_pos,
      const glm::vec2& drawable_size,
      const glm::vec2& map_size) {

    float target_x = target_pos.x - drawable_size.x * 0.5f;
    float target_y = target_pos.y - drawable_size.y * 0.5f;

    float max_camera_x = std::max(0.0f, map_size.x - drawable_size.x);
    float max_camera_y = std::max(0.0f, map_size.y - drawable_size.y);

    target_x = std::clamp(target_x, 0.0f, max_camera_x);
    target_y = std::clamp(target_y, 0.0f, max_camera_y);

    return {target_x, target_y, 0.0f};
  }
};

}  // namespace dnd_rogue::core::overworld

#endif  // DND_ROGUE_CORE_OVERWORLD_OVERWORLD_UTILS_H_
