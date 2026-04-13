#ifndef DND_ROGUE_CORE_SESSION_H_
#define DND_ROGUE_CORE_SESSION_H_

#include <memory>
#include <vector>

#include "core/models/character.h"

namespace dnd_rogue::core {

/**
 * @brief Singleton class to manage the current game session and party.
 */
class Session {
 public:
  static Session& Get() {
    static Session instance;
    return instance;
  }

  void InitRun(const std::vector<models::CharacterClass>& classes);

  const std::vector<models::Character>& GetParty() const { return party_; }

 private:
  Session() = default;
  ~Session() = default;
  Session(const Session&) = delete;
  Session& operator=(const Session&) = delete;

  std::vector<models::Character> party_;
};

}  // namespace dnd_rogue::core

#endif  // DND_ROGUE_CORE_SESSION_H_
