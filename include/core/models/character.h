#ifndef DND_ROGUE_CORE_MODELS_CHARACTER_H_
#define DND_ROGUE_CORE_MODELS_CHARACTER_H_

#include "core/models/character_class.h"

namespace dnd_rogue::core::models {

/**
 * @brief Container class for character data.
 */
class Character {
 public:
  Character(CharacterClass cls = CharacterClass::Fighter) : class_(cls) {}

  CharacterClass GetClass() const { return class_; }
  void SetClass(CharacterClass cls) { class_ = cls; }

 private:
  CharacterClass class_;
  // Future: stats, skills, items, etc.
};

}  // namespace dnd_rogue::core::models

#endif  // DND_ROGUE_CORE_MODELS_CHARACTER_H_
