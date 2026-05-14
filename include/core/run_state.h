#ifndef DND_ROGUE_CORE_RUN_STATE_H_
#define DND_ROGUE_CORE_RUN_STATE_H_

#include <cstdint>
#include <string>
#include <vector>

#include "core/card.h"
#include "core/commander.h"

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
   * @brief Serializes the current state into a byte buffer.
   */
  std::vector<uint8_t> Serialize() const;

  /**
   * @brief Deserializes the state from a byte buffer.
   * @param data The buffer containing serialized state.
   */
  void Deserialize(const std::vector<uint8_t>& data);

  // Run data accessors
  int32_t GetGold() const { return gold_; }
  void SetGold(int32_t gold) { gold_ = gold; }
  void AddGold(int32_t amount) { gold_ += amount; }

  const std::vector<Card>& GetCollection() const { return collection_; }
  void AddToCollection(const Card& card) { collection_.push_back(card); }

  const std::vector<Card>& GetDeck() const { return deck_; }
  void AddToDeck(const Card& card) { deck_.push_back(card); }

  const std::vector<Commander>& GetCommanders() const { return commanders_; }
  void AddCommander(const Commander& commander) {
    commanders_.push_back(commander);
  }

 private:
  RunState() = default;
  ~RunState() = default;

  // Stop copying and assignment
  RunState(const RunState&) = delete;
  RunState& operator=(const RunState&) = delete;

  uint64_t seed_ = 0;
  int32_t gold_ = 0;
  std::vector<Card> collection_;
  std::vector<Card> deck_;
  std::vector<Commander> commanders_;
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_RUN_STATE_H_
