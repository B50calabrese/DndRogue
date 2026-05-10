#ifndef DND_ROGUE_CORE_RUN_STATE_H_
#define DND_ROGUE_CORE_RUN_STATE_H_

#include <cstdint>
#include <string>
#include <vector>

namespace dnd_rogue::core {

/**
 * @brief Represents a character in the player's collection.
 */
struct Character {
  std::string name;
};

/**
 * @brief Represents a combat card in the player's collection.
 */
struct CombatCard {
  std::string name;
};

/**
 * @brief Represents an item in the player's collection.
 */
struct Item {
  std::string name;
};

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
  const std::vector<Character>& GetCharacters() const { return characters_; }

  /**
   * @brief Adds a character to the collection.
   */
  void AddCharacter(const Character& character) { characters_.push_back(character); }

  /**
   * @brief Returns the collection of combat cards.
   */
  const std::vector<CombatCard>& GetCombatCards() const { return combat_cards_; }

  /**
   * @brief Adds a combat card to the collection.
   */
  void AddCombatCard(const CombatCard& card) { combat_cards_.push_back(card); }

  /**
   * @brief Returns the collection of items.
   */
  const std::vector<Item>& GetItems() const { return items_; }

  /**
   * @brief Adds an item to the collection.
   */
  void AddItem(const Item& item) { items_.push_back(item); }

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
  std::vector<Character> characters_;
  std::vector<CombatCard> combat_cards_;
  std::vector<Item> items_;
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_RUN_STATE_H_
