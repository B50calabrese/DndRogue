#ifndef DND_ROGUE_CORE_BATTLE_BATTLE_UI_UTILS_H_
#define DND_ROGUE_CORE_BATTLE_BATTLE_UI_UTILS_H_

#include <engine/ecs/entity_manager.h>
#include <engine/ecs/registry.h>
#include <vector>
#include <string>

namespace dnd_rogue::core::battle {

class BattleUIUtils {
 public:
  struct LayoutInfo {
    float sw, sh;
    float sb_h, cb_h;
    float p_w, p_area_h;
  };

  static engine::ecs::EntityID CreateStatusBar(engine::ecs::Registry& registry);
  static engine::ecs::EntityID CreateCommandBar(engine::ecs::Registry& registry);
  static engine::ecs::EntityID CreatePortraits(engine::ecs::Registry& registry, std::vector<engine::ecs::EntityID>& portrait_entities);

  static void UpdateLayout(engine::ecs::Registry& registry,
                           LayoutInfo& info,
                           engine::ecs::EntityID status_bar,
                           engine::ecs::EntityID command_bar,
                           engine::ecs::EntityID portraits_container,
                           const std::vector<engine::ecs::EntityID>& portrait_entities);
};

} // namespace dnd_rogue::core::battle

#endif // DND_ROGUE_CORE_BATTLE_BATTLE_UI_UTILS_H_
