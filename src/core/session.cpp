#include "core/session.h"

namespace dnd_rogue::core {

void Session::InitRun(const std::vector<models::CharacterClass>& classes) {
  party_.clear();
  for (auto cls : classes) {
    party_.emplace_back(cls);
  }
}

}  // namespace dnd_rogue::core
