#ifndef DND_ROGUE_CORE_BATTLE_BATTLE_UI_MANAGER_H_
#define DND_ROGUE_CORE_BATTLE_BATTLE_UI_MANAGER_H_

#include <engine/ecs/entity_manager.h>
#include <engine/ecs/registry.h>
#include <vector>
#include <string>

namespace dnd_rogue::core::battle {

class BattleUIManager {
 public:
  struct LayoutInfo {
    float screen_width;
    float screen_height;
    float status_bar_height;
    float command_bar_height;
    float portrait_width;
    float portrait_area_height;
  };

  BattleUIManager(engine::ecs::Registry& registry);

  void UpdateLayout(const LayoutInfo& info);

  engine::ecs::EntityID status_bar() const { return status_bar_; }
  engine::ecs::EntityID command_bar() const { return command_bar_; }
  engine::ecs::EntityID portraits_container() const { return portraits_container_; }
  const std::vector<engine::ecs::EntityID>& portrait_entities() const { return portrait_entities_; }

 private:
  void CreateStatusBar();
  void CreateCommandBar();
  void CreatePortraits();

  void UpdateStatusBarLayout(const LayoutInfo& info);
  void UpdateCommandBarLayout(const LayoutInfo& info);
  void UpdatePortraitsLayout(const LayoutInfo& info);

  engine::ecs::Registry& registry_;
  engine::ecs::EntityID status_bar_ = engine::ecs::INVALID_ENTITY;
  engine::ecs::EntityID command_bar_ = engine::ecs::INVALID_ENTITY;
  engine::ecs::EntityID portraits_container_ = engine::ecs::INVALID_ENTITY;
  std::vector<engine::ecs::EntityID> portrait_entities_;
};

} // namespace dnd_rogue::core::battle

#endif // DND_ROGUE_CORE_BATTLE_BATTLE_UI_MANAGER_H_
