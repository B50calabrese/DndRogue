#include "dnd_rogue_app.h"

#include <iostream>
#include "engine/util/logger.h"

void DndRogueApp::OnInit() {
  LOG_INFO("DndRogueApp: Initializing...");
}

void DndRogueApp::OnUpdate(double delta_time_seconds) {
  // Game logic update loop
}

void DndRogueApp::OnShutdown() {
  LOG_INFO("DndRogueApp: Shutting down...");
}
