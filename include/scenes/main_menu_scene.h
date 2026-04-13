#ifndef DND_ROGUE_SCENES_MAIN_MENU_SCENE_H_
#define DND_ROGUE_SCENES_MAIN_MENU_SCENE_H_

#include <engine/scene/scene.h>
#include <glm/glm.hpp>

namespace dnd_rogue::scenes {

/**
 * @brief Scene for the main menu of the game.
 *
 * This scene is responsible for displaying the initial menu to the user,
 * allowing them to start a new run, adjust settings, or quit.
 */
class MainMenuScene : public engine::Scene {
 public:
  MainMenuScene();
  ~MainMenuScene() override = default;

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate(float delta_time_seconds) override;
  void OnRender() override;
  bool OnInput() override;

 private:
  // UI Constants
  static constexpr float kButtonWidthPercent = 0.8f;
  static constexpr float kButtonHeightPercent = 0.1f;

  // Colors
  static constexpr glm::vec4 kBackgroundColor = {0.95f, 0.95f, 0.95f, 1.0f};  // Off-white
  static constexpr glm::vec4 kButtonInteriorColor = {0.5f, 0.0f, 0.0f, 1.0f}; // Dark red
  static constexpr glm::vec4 kButtonHoverColor = {0.0f, 0.5f, 0.0f, 1.0f};    // Green
  static constexpr glm::vec4 kButtonBorderColor = {0.0f, 0.0f, 0.0f, 1.0f};   // Black
  static constexpr glm::vec4 kTextColor = {1.0f, 1.0f, 1.0f, 1.0f};          // White
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_MAIN_MENU_SCENE_H_
