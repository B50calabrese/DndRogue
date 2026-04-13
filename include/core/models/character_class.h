#ifndef DND_ROGUE_CORE_MODELS_CHARACTER_CLASS_H_
#define DND_ROGUE_CORE_MODELS_CHARACTER_CLASS_H_

#include <string>

#include <glm/glm.hpp>

namespace dnd_rogue::core::models {

enum class CharacterClass {
  Fighter,
  Monk,
  Paladin,
  Ranger,
  Barbarian,
  Wizard,
  Cleric,
  Sorcerer,
  Warlock,
  Bard,
  Rogue,
  Druid
};

inline std::string GetCharacterClassName(CharacterClass cls) {
  switch (cls) {
    case CharacterClass::Fighter:
      return "Fighter";
    case CharacterClass::Monk:
      return "Monk";
    case CharacterClass::Paladin:
      return "Paladin";
    case CharacterClass::Ranger:
      return "Ranger";
    case CharacterClass::Barbarian:
      return "Barbarian";
    case CharacterClass::Wizard:
      return "Wizard";
    case CharacterClass::Cleric:
      return "Cleric";
    case CharacterClass::Sorcerer:
      return "Sorcerer";
    case CharacterClass::Warlock:
      return "Warlock";
    case CharacterClass::Bard:
      return "Bard";
    case CharacterClass::Rogue:
      return "Rogue";
    case CharacterClass::Druid:
      return "Druid";
    default:
      return "Unknown";
  }
}

inline glm::vec4 GetCharacterClassColor(CharacterClass cls) {
  switch (cls) {
    case CharacterClass::Fighter:
      return {0.7f, 0.2f, 0.2f, 1.0f};  // Red-ish
    case CharacterClass::Monk:
      return {0.3f, 0.7f, 0.9f, 1.0f};  // Sky Blue
    case CharacterClass::Paladin:
      return {0.9f, 0.8f, 0.3f, 1.0f};  // Gold
    case CharacterClass::Ranger:
      return {0.2f, 0.6f, 0.2f, 1.0f};  // Forest Green
    case CharacterClass::Barbarian:
      return {0.9f, 0.4f, 0.1f, 1.0f};  // Orange
    case CharacterClass::Wizard:
      return {0.2f, 0.3f, 0.8f, 1.0f};  // Blue
    case CharacterClass::Cleric:
      return {0.8f, 0.8f, 0.8f, 1.0f};  // White/Grey
    case CharacterClass::Sorcerer:
      return {0.6f, 0.1f, 0.1f, 1.0f};  // Dark Red
    case CharacterClass::Warlock:
      return {0.5f, 0.2f, 0.7f, 1.0f};  // Purple
    case CharacterClass::Bard:
      return {0.8f, 0.4f, 0.8f, 1.0f};  // Pink/Magenta
    case CharacterClass::Rogue:
      return {0.3f, 0.3f, 0.3f, 1.0f};  // Dark Grey
    case CharacterClass::Druid:
      return {0.5f, 0.4f, 0.2f, 1.0f};  // Brown/Earth
    default:
      return {1.0f, 1.0f, 1.0f, 1.0f};
  }
}

}  // namespace dnd_rogue::core::models

#endif  // DND_ROGUE_CORE_MODELS_CHARACTER_CLASS_H_
