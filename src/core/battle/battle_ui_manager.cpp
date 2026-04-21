#include "core/battle/battle_ui_manager.h"
#include <engine/ui/ui_components.h>
#include <engine/ecs/components/quad.h>
#include <engine/ecs/components/text.h>

namespace dnd_rogue::core::battle {

BattleUIManager::BattleUIManager(engine::ecs::Registry& registry) : registry_(registry) {
  CreateStatusBar();
  CreateCommandBar();
  CreatePortraits();
}

void BattleUIManager::CreateStatusBar() {
  status_bar_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(status_bar_, engine::ui::UITransform{});
  registry_.AddComponent<engine::ecs::components::Quad>(
      status_bar_, engine::ecs::components::Quad{{0.5f, 0.5f, 0.5f, 1.0f}});

  engine::ecs::EntityID status_text = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(status_text, engine::ui::UITransform{});
  registry_.AddComponent<engine::ecs::components::Text>(
      status_text, engine::ecs::components::Text{"Status Bar", "battle_font", 1.0f, {1, 1, 1, 1}});
  registry_.AddComponent<engine::ui::UIHierarchy>(status_text, engine::ui::UIHierarchy{status_bar_});
  registry_.AddComponent<engine::ui::UIHierarchy>(status_bar_, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, {status_text}});
}

void BattleUIManager::CreateCommandBar() {
  command_bar_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(command_bar_, engine::ui::UITransform{});
  registry_.AddComponent<engine::ecs::components::Quad>(
      command_bar_, engine::ecs::components::Quad{{0.3f, 0.3f, 0.3f, 1.0f}});

  std::vector<engine::ecs::EntityID> slots;
  for (int i = 0; i < 20; ++i) {
    engine::ecs::EntityID slot = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(slot, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        slot, engine::ecs::components::Quad{{0.4f, 0.4f, 0.4f, 1.0f}});

    engine::ecs::EntityID slot_text = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(slot_text, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Text>(
        slot_text, engine::ecs::components::Text{std::to_string(i + 1), "small_battle_font", 0.8f, {1, 1, 1, 1}});

    registry_.AddComponent<engine::ui::UIHierarchy>(slot_text, engine::ui::UIHierarchy{slot});
    registry_.AddComponent<engine::ui::UIHierarchy>(slot, engine::ui::UIHierarchy{command_bar_, {slot_text}});
    slots.push_back(slot);
  }
  registry_.AddComponent<engine::ui::UIHierarchy>(command_bar_, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, slots});
}

void BattleUIManager::CreatePortraits() {
  portraits_container_ = registry_.CreateEntity();
  registry_.AddComponent<engine::ui::UITransform>(portraits_container_, engine::ui::UITransform{});

  portrait_entities_.clear();
  for (int i = 0; i < 4; ++i) {
    engine::ecs::EntityID portrait = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(portrait, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        portrait, engine::ecs::components::Quad{{0.2f, 0.2f, 0.2f, 1.0f}});

    engine::ecs::EntityID hb_bg = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(hb_bg, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        hb_bg, engine::ecs::components::Quad{{1.0f, 0.0f, 0.0f, 1.0f}});

    engine::ecs::EntityID hb_fill = registry_.CreateEntity();
    registry_.AddComponent<engine::ui::UITransform>(hb_fill, engine::ui::UITransform{});
    registry_.AddComponent<engine::ecs::components::Quad>(
        hb_fill, engine::ecs::components::Quad{{0.0f, 1.0f, 0.0f, 1.0f}});

    registry_.AddComponent<engine::ui::UIHierarchy>(hb_bg, engine::ui::UIHierarchy{portrait});
    registry_.AddComponent<engine::ui::UIHierarchy>(hb_fill, engine::ui::UIHierarchy{portrait});
    registry_.AddComponent<engine::ui::UIHierarchy>(portrait, engine::ui::UIHierarchy{portraits_container_, {hb_bg, hb_fill}});
    portrait_entities_.push_back(portrait);
  }
  registry_.AddComponent<engine::ui::UIHierarchy>(portraits_container_, engine::ui::UIHierarchy{engine::ecs::INVALID_ENTITY, portrait_entities_});
}

void BattleUIManager::UpdateLayout(const LayoutInfo& info) {
  UpdateStatusBarLayout(info);
  UpdateCommandBarLayout(info);
  UpdatePortraitsLayout(info);
}

void BattleUIManager::UpdateStatusBarLayout(const LayoutInfo& info) {
  engine::ui::UITransform& sb_t = registry_.GetComponent<engine::ui::UITransform>(status_bar_);
  sb_t.local_pos = {0, 0};
  sb_t.size = {info.screen_width, info.status_bar_height};
  sb_t.z_index = 150;

  engine::ui::UIHierarchy& sb_hie = registry_.GetComponent<engine::ui::UIHierarchy>(status_bar_);
  engine::ui::UITransform& sb_text_t = registry_.GetComponent<engine::ui::UITransform>(sb_hie.children[0]);
  sb_text_t.local_pos = {info.screen_width * 0.5f, info.status_bar_height * 0.5f};
}

void BattleUIManager::UpdateCommandBarLayout(const LayoutInfo& info) {
  engine::ui::UITransform& cb_t = registry_.GetComponent<engine::ui::UITransform>(command_bar_);
  cb_t.local_pos = {0, info.screen_height - info.command_bar_height};
  cb_t.size = {info.screen_width, info.command_bar_height};
  cb_t.z_index = 150;

  engine::ui::UIHierarchy& cb_hie = registry_.GetComponent<engine::ui::UIHierarchy>(command_bar_);
  float slot_w = info.screen_width / 10.0f;
  float slot_h = info.command_bar_height / 2.0f;
  for (int i = 0; i < 20; ++i) {
    engine::ecs::EntityID slot_ent = cb_hie.children[i];
    engine::ui::UITransform& slot_t = registry_.GetComponent<engine::ui::UITransform>(slot_ent);
    int row = i / 10;
    int col = i % 10;
    slot_t.local_pos = {col * slot_w + 2.0f, row * slot_h + 2.0f};
    slot_t.size = {slot_w - 4.0f, slot_h - 4.0f};

    engine::ui::UIHierarchy& slot_hie = registry_.GetComponent<engine::ui::UIHierarchy>(slot_ent);
    engine::ui::UITransform& slot_text_t = registry_.GetComponent<engine::ui::UITransform>(slot_hie.children[0]);
    slot_text_t.local_pos = {slot_t.size.x * 0.5f, slot_t.size.y * 0.5f};
  }
}

void BattleUIManager::UpdatePortraitsLayout(const LayoutInfo& info) {
  engine::ui::UITransform& pc_t = registry_.GetComponent<engine::ui::UITransform>(portraits_container_);
  pc_t.local_pos = {0, info.status_bar_height};
  pc_t.size = {info.portrait_width, info.portrait_area_height};

  float p_h = info.portrait_area_height / 4.0f;
  for (int i = 0; i < 4; ++i) {
    engine::ecs::EntityID p_ent = portrait_entities_[i];
    engine::ui::UITransform& p_t = registry_.GetComponent<engine::ui::UITransform>(p_ent);
    p_t.local_pos = {5.0f, i * p_h + 5.0f};
    p_t.size = {info.portrait_width - 10.0f, p_h - 10.0f};

    engine::ui::UIHierarchy& p_hie = registry_.GetComponent<engine::ui::UIHierarchy>(p_ent);
    float hb_h = 10.0f;
    engine::ui::UITransform& hb_bg_t = registry_.GetComponent<engine::ui::UITransform>(p_hie.children[0]);
    hb_bg_t.local_pos = {0, p_t.size.y - hb_h};
    hb_bg_t.size = {p_t.size.x, hb_h};

    engine::ui::UITransform& hb_fill_t = registry_.GetComponent<engine::ui::UITransform>(p_hie.children[1]);
    hb_fill_t.local_pos = {0, p_t.size.y - hb_h};
    hb_fill_t.size = {p_t.size.x * 0.8f, hb_h};
  }
}

} // namespace dnd_rogue::core::battle
