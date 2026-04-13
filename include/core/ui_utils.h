#ifndef DND_ROGUE_CORE_UI_UTILS_H_
#define DND_ROGUE_CORE_UI_UTILS_H_

#include <string>
#include <functional>
#include <glm/glm.hpp>
#include "engine/ecs/registry.h"
#include "engine/ecs/entity_manager.h"

namespace dnd_rogue::core {

/**
 * @brief Utility for creating standardized buttons in the game.
 */
class UIUtils {
 public:
  /**
   * @brief Creates a button with a border and centered text.
   *
   * @param registry The ECS registry to create entities in.
   * @param position The position of the button.
   * @param size The size of the button.
   * @param text The text to display on the button.
   * @param font_name The name of the font to use.
   * @param interior_color The default color of the button.
   * @param hover_color The color of the button when hovered.
   * @param border_color The color of the button's border.
   * @param text_color The color of the text.
   * @param on_click The callback to trigger when the button is clicked.
   * @return The EntityID of the main button entity.
   */
  static engine::ecs::EntityID CreateButton(
      engine::ecs::Registry& registry,
      const glm::vec2& position,
      const glm::vec2& size,
      const std::string& text,
      const std::string& font_name,
      const glm::vec4& interior_color,
      const glm::vec4& hover_color,
      const glm::vec4& border_color,
      const glm::vec4& text_color,
      std::function<void()> on_click);
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_UI_UTILS_H_
