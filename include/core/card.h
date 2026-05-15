#ifndef DND_ROGUE_CORE_CARD_H_
#define DND_ROGUE_CORE_CARD_H_

#include <string>

namespace dnd_rogue::core {

/**
 * @brief Represents a card in the game.
 */
struct Card {
  std::string id;
  std::string name;
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_CARD_H_
