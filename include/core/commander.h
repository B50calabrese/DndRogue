#ifndef DND_ROGUE_CORE_COMMANDER_H_
#define DND_ROGUE_CORE_COMMANDER_H_

#include <string>

namespace dnd_rogue::core {

/**
 * @brief Represents a commander in the game.
 */
struct Commander {
  std::string id;
  std::string name;
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_COMMANDER_H_
