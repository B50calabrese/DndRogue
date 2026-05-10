#ifndef DND_ROGUE_CORE_COLLECTION_COMBAT_CARD_H_
#define DND_ROGUE_CORE_COLLECTION_COMBAT_CARD_H_

#include <string>

namespace dnd_rogue::core::collection {

/**
 * @brief Represents a combat card in the player's collection.
 */
struct CombatCard {
  std::string name;
};

}  // namespace dnd_rogue::core::collection

#endif  // DND_ROGUE_CORE_COLLECTION_COMBAT_CARD_H_
