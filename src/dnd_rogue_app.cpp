#include "dnd_rogue_app.h"

#include <iostream>
#include <memory>

#include "core/data_registry.h"
#include "engine/scene/scene_manager.h"
#include "engine/util/logger.h"
#include "scenes/main_menu_scene.h"

void DndRogueApp::OnInit() {
  LOG_INFO("DndRogueApp: Initializing...");

  // Load game data
  dnd_rogue::core::DataRegistry::Get().LoadAll(ENGINE_ASSETS_PATH);

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
