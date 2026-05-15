#ifndef DND_ROGUE_CORE_DATA_REGISTRY_H_
#define DND_ROGUE_CORE_DATA_REGISTRY_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "core/card.h"
#include "core/commander.h"

namespace dnd_rogue::core {

/**
 * @brief Singleton registry for game data (cards, commanders, etc.).
 */
class DataRegistry {
 public:
  static DataRegistry& Get();

  /**
   * @brief Loads all data from the assets directory.
   * @param assets_path Path to the assets directory.
   */
  void LoadAll(const std::string& assets_path);

  const Card* GetCard(const std::string& id) const;
  const Commander* GetCommander(const std::string& id) const;

  const std::unordered_map<std::string, Card>& GetCards() const { return cards_; }
  const std::unordered_map<std::string, Commander>& GetCommanders() const {
    return commanders_;
  }

 private:
  DataRegistry() = default;
  ~DataRegistry() = default;

  DataRegistry(const DataRegistry&) = delete;
  DataRegistry& operator=(const DataRegistry&) = delete;

  void LoadCards(const std::string& cards_path);
  void LoadCommanders(const std::string& commanders_path);

  std::unordered_map<std::string, Card> cards_;
  std::unordered_map<std::string, Commander> commanders_;
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_DATA_REGISTRY_H_
