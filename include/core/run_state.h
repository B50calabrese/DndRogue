#ifndef DND_ROGUE_CORE_RUN_STATE_H_
#define DND_ROGUE_CORE_RUN_STATE_H_

#include <cstdint>
#include <vector>

#include "core/collection/character.h"
#include "core/collection/combat_card.h"
#include "core/collection/item.h"

namespace dnd_rogue::core {

/**
 * @brief Represents the current state of a game run.
 *
 * This is a singleton that holds data shared across all scenes during a run.
 */
class RunState {
 public:
  /**
   * @brief Access the singleton instance.
   */
  static RunState& Get();

  /**
   * @brief Initializes or resets the run state with a given seed.
   * @param seed The random seed for this run.
   */
  void Initialize(uint64_t seed);

  /**
   * @brief Returns the random seed for the current run.
   */
  uint64_t GetSeed() const { return seed_; }

  /**
   * @brief Returns the current amount of gold.
   */
  int32_t GetGold() const { return gold_; }

  /**
   * @brief Sets the current amount of gold.
   */
  void SetGold(int32_t gold) { gold_ = gold; }

  /**
   * @brief Adds to the current amount of gold.
   */
  void AddGold(int32_t amount) { gold_ += amount; }

  /**
   * @brief Returns the collection of characters.
   */
  const std::vector<collection::Character>& GetCharacters() const { return characters_; }

  /**
   * @brief Adds a character to the collection.
   */
  void AddCharacter(const collection::Character& character) { characters_.push_back(character); }

  /**
   * @brief Removes a character from the collection by index.
   */
  void RemoveCharacter(size_t index) {
    if (index < characters_.size()) {
      characters_.erase(characters_.begin() + index);
    }
  }

  /**
   * @brief Returns the collection of combat cards.
   */
  const std::vector<collection::CombatCard>& GetCombatCards() const { return combat_cards_; }

  /**
   * @brief Adds a combat card to the collection.
   */
  void AddCombatCard(const collection::CombatCard& card) { combat_cards_.push_back(card); }

  /**
   * @brief Removes a combat card from the collection by index.
   */
  void RemoveCombatCard(size_t index) {
    if (index < combat_cards_.size()) {
      combat_cards_.erase(combat_cards_.begin() + index);
    }
  }

  /**
   * @brief Returns the collection of items.
   */
  const std::vector<collection::Item>& GetItems() const { return items_; }

  /**
   * @brief Adds an item to the collection.
   */
  void AddItem(const collection::Item& item) { items_.push_back(item); }

  /**
   * @brief Removes an item from the collection by index.
   */
  void RemoveItem(size_t index) {
    if (index < items_.size()) {
      items_.erase(items_.begin() + index);
    }
  }

  /**
   * @brief Serializes the current state into a byte buffer.
   */
  std::vector<uint8_t> Serialize() const;

  /**
   * @brief Deserializes the state from a byte buffer.
   * @param data The buffer containing serialized state.
   */
  void Deserialize(const std::vector<uint8_t>& data);

 private:
  RunState() = default;
  ~RunState() = default;

  // Stop copying and assignment
  RunState(const RunState&) = delete;
  RunState& operator=(const RunState&) = delete;

  uint64_t seed_ = 0;
  int32_t gold_ = 0;
  std::vector<collection::Character> characters_;
  std::vector<collection::CombatCard> combat_cards_;
  std::vector<collection::Item> items_;
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_RUN_STATE_H_
