#include "dnd_rogue_app.h"
#include "core/constants.h"
#include "engine/core/engine.h"
#include "engine/util/logger.h"

/**
 * @brief Entry point for the DndRogue application.
 */
int main() {
  LOG_INFO("Starting DndRogue...");

  // Engine configuration
  engine::EngineConfig engine_config;
  engine_config.asset_path = ENGINE_ASSETS_PATH;
  engine_config.window_width = dnd_rogue::core::kWindowWidth;
  engine_config.window_height = dnd_rogue::core::kWindowHeight;

  // Initialize the engine
  engine::Engine::Init(engine_config);

  // Create and run the application
  DndRogueApp app;
  app.Run();

  return 0;
}
