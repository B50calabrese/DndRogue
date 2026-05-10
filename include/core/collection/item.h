#ifndef DND_ROGUE_CORE_COLLECTION_ITEM_H_
#define DND_ROGUE_CORE_COLLECTION_ITEM_H_

#include <string>

namespace dnd_rogue::core::collection {

/**
 * @brief Represents an item in the player's collection.
 */
struct Item {
  std::string name;
};

}  // namespace dnd_rogue::core::collection

#endif  // DND_ROGUE_CORE_COLLECTION_ITEM_H_
