#ifndef DND_ROGUE_SCENES_MAIN_MENU_SCENE_H_
#define DND_ROGUE_SCENES_MAIN_MENU_SCENE_H_

#include <engine/scene/scene.h>

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
};

}  // namespace dnd_rogue::scenes

#endif  // DND_ROGUE_SCENES_MAIN_MENU_SCENE_H_
