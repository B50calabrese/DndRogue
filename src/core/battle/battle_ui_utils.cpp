#include "core/battle/battle_ui_utils.h"
#include <engine/ui/ui_components.h>
#include <engine/ecs/components/quad.h>
#include <engine/ecs/components/text.h>

namespace dnd_rogue::core::battle {

engine::ecs::EntityID BattleUIUtils::CreateStatusBar(engine::ecs::Registry& registry) {
  auto status_bar = registry.CreateEntity();
  registry.AddComponent<engine::ui::UITransform>(status_bar, engine::ui::UITransform{});
  registry.AddComponent<engine::ecs::components::Quad>(
      status_bar, engine::ecs::components::Quad{{0.5f, 0.5f, 0.5f, 1.0f}});

  auto status_text = registry.CreateEntity();
  registry.AddComponent<engine::ui::UITransform>(status_text, engine::ui::UITransform{});
  registry.AddComponent<engine::ecs::components::Text>(
      status_text, engine::ecs::components::Text{"Status Bar", "battle_font", 1.0f, {1, 1, 1, 1}});
  registry.AddComponent<engine::ui::UIHierarchy>(status_text, engine::ui::UIHierarchy{status_bar});
  registry.AddComponent<engine::ui::UIHierarchy>(status_bar, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, {status_text}});
  return status_bar;
}

engine::ecs::EntityID BattleUIUtils::CreateCommandBar(engine::ecs::Registry& registry) {
  auto command_bar = registry.CreateEntity();
  registry.AddComponent<engine::ui::UITransform>(command_bar, engine::ui::UITransform{});
  registry.AddComponent<engine::ecs::components::Quad>(
      command_bar, engine::ecs::components::Quad{{0.3f, 0.3f, 0.3f, 1.0f}});

  std::vector<engine::ecs::EntityID> slots;
  for (int i = 0; i < 20; ++i) {
    auto slot = registry.CreateEntity();
    registry.AddComponent<engine::ui::UITransform>(slot, engine::ui::UITransform{});
    registry.AddComponent<engine::ecs::components::Quad>(
        slot, engine::ecs::components::Quad{{0.4f, 0.4f, 0.4f, 1.0f}});

    auto slot_text = registry.CreateEntity();
    registry.AddComponent<engine::ui::UITransform>(slot_text, engine::ui::UITransform{});
    registry.AddComponent<engine::ecs::components::Text>(
        slot_text, engine::ecs::components::Text{std::to_string(i + 1), "small_battle_font", 0.8f, {1, 1, 1, 1}});

    registry.AddComponent<engine::ui::UIHierarchy>(slot_text, engine::ui::UIHierarchy{slot});
    registry.AddComponent<engine::ui::UIHierarchy>(slot, engine::ui::UIHierarchy{command_bar, {slot_text}});
    slots.push_back(slot);
  }
  registry.AddComponent<engine::ui::UIHierarchy>(command_bar, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, slots});
  return command_bar;
}

engine::ecs::EntityID BattleUIUtils::CreatePortraits(engine::ecs::Registry& registry, std::vector<engine::ecs::EntityID>& portrait_entities) {
  auto portraits_container = registry.CreateEntity();
  registry.AddComponent<engine::ui::UITransform>(portraits_container, engine::ui::UITransform{});

  portrait_entities.clear();
  for (int i = 0; i < 4; ++i) {
    auto portrait = registry.CreateEntity();
    registry.AddComponent<engine::ui::UITransform>(portrait, engine::ui::UITransform{});
    registry.AddComponent<engine::ecs::components::Quad>(
        portrait, engine::ecs::components::Quad{{0.2f, 0.2f, 0.2f, 1.0f}});

    auto hb_bg = registry.CreateEntity();
    registry.AddComponent<engine::ui::UITransform>(hb_bg, engine::ui::UITransform{});
    registry.AddComponent<engine::ecs::components::Quad>(
        hb_bg, engine::ecs::components::Quad{{1.0f, 0.0f, 0.0f, 1.0f}});

    auto hb_fill = registry.CreateEntity();
    registry.AddComponent<engine::ui::UITransform>(hb_fill, engine::ui::UITransform{});
    registry.AddComponent<engine::ecs::components::Quad>(
        hb_fill, engine::ecs::components::Quad{{0.0f, 1.0f, 0.0f, 1.0f}});

    registry.AddComponent<engine::ui::UIHierarchy>(hb_bg, engine::ui::UIHierarchy{portrait});
    registry.AddComponent<engine::ui::UIHierarchy>(hb_fill, engine::ui::UIHierarchy{portrait});
    registry.AddComponent<engine::ui::UIHierarchy>(portrait, engine::ui::UIHierarchy{portraits_container, {hb_bg, hb_fill}});
    portrait_entities.push_back(portrait);
  }
  registry.AddComponent<engine::ui::UIHierarchy>(portraits_container, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, portrait_entities});
  return portraits_container;
}

void BattleUIUtils::UpdateLayout(engine::ecs::Registry& registry,
                                 LayoutInfo& info,
                                 engine::ecs::EntityID status_bar,
                                 engine::ecs::EntityID command_bar,
                                 engine::ecs::EntityID portraits_container,
                                 const std::vector<engine::ecs::EntityID>& portrait_entities) {
  // Status Bar
  auto& sb_t = registry.GetComponent<engine::ui::UITransform>(status_bar);
  sb_t.local_pos = {0, 0};
  sb_t.size = {info.sw, info.sb_h};
  sb_t.z_index = 150;

  auto& sb_hie = registry.GetComponent<engine::ui::UIHierarchy>(status_bar);
  auto& sb_text_t = registry.GetComponent<engine::ui::UITransform>(sb_hie.children[0]);
  sb_text_t.local_pos = {info.sw * 0.5f, info.sb_h * 0.5f};

  // Command Bar
  auto& cb_t = registry.GetComponent<engine::ui::UITransform>(command_bar);
  cb_t.local_pos = {0, info.sh - info.cb_h};
  cb_t.size = {info.sw, info.cb_h};
  cb_t.z_index = 150;

  auto& cb_hie = registry.GetComponent<engine::ui::UIHierarchy>(command_bar);
  float slot_w = info.sw / 10.0f;
  float slot_h = info.cb_h / 2.0f;
  for (int i = 0; i < 20; ++i) {
    auto slot_ent = cb_hie.children[i];
    auto& slot_t = registry.GetComponent<engine::ui::UITransform>(slot_ent);
    int row = i / 10;
    int col = i % 10;
    slot_t.local_pos = {col * slot_w + 2.0f, row * slot_h + 2.0f};
    slot_t.size = {slot_w - 4.0f, slot_h - 4.0f};

    auto& slot_hie = registry.GetComponent<engine::ui::UIHierarchy>(slot_ent);
    auto& slot_text_t = registry.GetComponent<engine::ui::UITransform>(slot_hie.children[0]);
    slot_text_t.local_pos = {slot_t.size.x * 0.5f, slot_t.size.y * 0.5f};
  }

  // Portraits
  auto& pc_t = registry.GetComponent<engine::ui::UITransform>(portraits_container);
  pc_t.local_pos = {0, info.sb_h};
  pc_t.size = {info.p_w, info.p_area_h};

  float p_h = info.p_area_h / 4.0f;
  for (int i = 0; i < 4; ++i) {
    auto p_ent = portrait_entities[i];
    auto& p_t = registry.GetComponent<engine::ui::UITransform>(p_ent);
    p_t.local_pos = {5.0f, i * p_h + 5.0f};
    p_t.size = {info.p_w - 10.0f, p_h - 10.0f};

    auto& p_hie = registry.GetComponent<engine::ui::UIHierarchy>(p_ent);
    float hb_h = 10.0f;
    auto& hb_bg_t = registry.GetComponent<engine::ui::UITransform>(p_hie.children[0]);
    hb_bg_t.local_pos = {0, p_t.size.y - hb_h};
    hb_bg_t.size = {p_t.size.x, hb_h};

    auto& hb_fill_t = registry.GetComponent<engine::ui::UITransform>(p_hie.children[1]);
    hb_fill_t.local_pos = {0, p_t.size.y - hb_h};
    hb_fill_t.size = {p_t.size.x * 0.8f, hb_h};
  }
}

} // namespace dnd_rogue::core::battle
