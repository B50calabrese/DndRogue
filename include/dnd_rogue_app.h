#ifndef DND_ROGUE_APP_H_
#define DND_ROGUE_APP_H_

#include "engine/core/application.h"

/**
 * @brief Main Application class for DndRogue.
 *
 * Inherits from engine::Application and implements the basic lifecycle methods.
 */
class DndRogueApp : public engine::Application {
 public:
  DndRogueApp() = default;

  /**
   * @brief Called when the application is initialized.
   */
  void OnInit() override;

  /**
   * @brief Called every frame to update game logic.
   * @param delta_time_seconds Time elapsed since the last frame.
   */
  void OnUpdate(double delta_time_seconds) override;

  /**
   * @brief Called when the application is shutting down.
   */
  void OnShutdown() override;
};

#endif  // DND_ROGUE_APP_H_
