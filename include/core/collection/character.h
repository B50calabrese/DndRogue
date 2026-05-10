#ifndef DND_ROGUE_CORE_COLLECTION_CHARACTER_H_
#define DND_ROGUE_CORE_COLLECTION_CHARACTER_H_

#include <string>

namespace dnd_rogue::core::collection {

/**
 * @brief Represents a character in the player's collection.
 */
struct Character {
  std::string name;
};

}  // namespace dnd_rogue::core::collection

#endif  // DND_ROGUE_CORE_COLLECTION_CHARACTER_H_
