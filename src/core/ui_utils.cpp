#include "core/ui_utils.h"
#include "engine/ui/ui_components.h"
#include "engine/ecs/components/quad.h"
#include "engine/ecs/components/text.h"

namespace dnd_rogue::core {

engine::ecs::EntityID UIUtils::CreateButton(
    engine::ecs::Registry& registry,
    const glm::vec2& position,
    const glm::vec2& size,
    const std::string& text,
    const std::string& font_name,
    const glm::vec4& interior_color,
    const glm::vec4& hover_color,
    const glm::vec4& border_color,
    const glm::vec4& text_color,
    std::function<void()> on_click) {

  // Create Border
  auto border_entity = registry.CreateEntity();
  registry.AddComponent<engine::ui::UITransform>(
      border_entity, engine::ui::UITransform{{position.x - 2, position.y - 2},
                                            {size.x + 4, size.y + 4}});
  registry.AddComponent<engine::ecs::components::Quad>(
      border_entity, engine::ecs::components::Quad{border_color, {0, 0}, 0.5f});

  // Create Button
  auto button_entity = registry.CreateEntity();
  registry.AddComponent<engine::ui::UITransform>(
      button_entity, engine::ui::UITransform{position, size});
  registry.AddComponent<engine::ecs::components::Quad>(
      button_entity, engine::ecs::components::Quad{interior_color, {0, 0}, 1.0f});

  // Create Text
  auto text_entity = registry.CreateEntity();
  registry.AddComponent<engine::ui::UITransform>(
      text_entity, engine::ui::UITransform{{size.x * 0.5f, size.y * 0.5f}, {0, 0}});
  registry.AddComponent<engine::ecs::components::Text>(
      text_entity, engine::ecs::components::Text{text, font_name, 1.0f, text_color, 2.0f});

  // Set up Hierarchy
  registry.AddComponent<engine::ui::UIHierarchy>(
      button_entity, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, {text_entity}});
  registry.AddComponent<engine::ui::UIHierarchy>(
      text_entity, engine::ui::UIHierarchy{button_entity});

  // Set up Interaction
  registry.AddComponent<engine::ui::UIInteractable>(
      button_entity,
      engine::ui::UIInteractable{
          false, false,
          on_click,
          [&registry, button_entity, interior_color, hover_color](bool hovered) {
            if (registry.HasComponent<engine::ecs::components::Quad>(button_entity)) {
              auto& quad = registry.GetComponent<engine::ecs::components::Quad>(button_entity);
              quad.color = hovered ? hover_color : interior_color;
            }
          }
      });

  return button_entity;
}

}  // namespace dnd_rogue::core
