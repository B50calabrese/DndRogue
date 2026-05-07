#ifndef DND_ROGUE_CORE_MATH_UTILS_H_
#define DND_ROGUE_CORE_MATH_UTILS_H_

#include <glm/glm.hpp>
#include "engine/graphics/camera.h"

namespace dnd_rogue::core {

/**
 * @brief Converts screen coordinates to world coordinates using a camera.
 *
 * @param screen_pos The position in screen space (pixels).
 * @param camera The camera defining the view.
 * @param window_width The width of the window.
 * @param window_height The height of the window.
 * @return The position in world space.
 */
glm::vec2 ScreenToWorld(const glm::vec2& screen_pos,
                        const engine::graphics::Camera& camera,
                        int window_width, int window_height);

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_MATH_UTILS_H_
