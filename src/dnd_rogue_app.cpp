#include "dnd_rogue_app.h"

#include <iostream>
#include <memory>

#include "engine/scene/scene_manager.h"
#include "engine/util/logger.h"
#include "scenes/main_menu_scene.h"

void DndRogueApp::OnInit() {
  LOG_INFO("DndRogueApp: Initializing...");

  // Set the initial scene to the main menu.
  engine::SceneManager::Get().SetScene(
      std::make_unique<dnd_rogue::scenes::MainMenuScene>());
}

void DndRogueApp::OnUpdate(double delta_time_seconds) {
  // Game logic update loop
}

void DndRogueApp::OnShutdown() {
  LOG_INFO("DndRogueApp: Shutting down...");
}
