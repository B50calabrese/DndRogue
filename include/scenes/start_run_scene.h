#ifndef DND_ROGUE_SCENES_START_RUN_SCENE_H_
#define DND_ROGUE_SCENES_START_RUN_SCENE_H_

#include <array>
#include <vector>

#include <engine/scene/scene.h>

#include "core/models/character_class.h"
#include "engine/ecs/entity_manager.h"

namespace dnd_rogue::scenes {

/**
 * @brief Scene for starting a new run.
 */
class StartRunScene : public engine::Scene {
 public:
  StartRunScene();
  ~StartRunScene() override = default;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float delta_time_seconds) override;
  void OnRender() override;
  bool OnInput() override;

 private:
  void CreateUI();
  void UpdateCharacterUI(int index);
  void ShowPicker(int index);
  void HidePicker();
  void DestroyEntityRecursive(engine::ecs::EntityID entity);

  std::array<core::models::CharacterClass, 4> selected_classes_;
  std::array<engine::ecs::EntityID, 4> class_squares_;
  std::array<engine::ecs::EntityID, 4> class_texts_;

  engine::ecs::EntityID picker_container_ = engine::ecs::INVALID_ENTITY;
  engine::ecs::EntityID click_out_overlay_ = engine::ecs::INVALID_ENTITY;
  int active_picker_index_ = -1;

  const glm::vec4 kGreenColor = {0.2f, 0.8f, 0.2f, 1.0f};
  const glm::vec4 kPickerBackgroundColor = {0.15f, 0.15f, 0.15f, 0.95f};
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_START_RUN_SCENE_H_
