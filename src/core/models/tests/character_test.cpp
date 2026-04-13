#include <gtest/gtest.h>
#include "core/models/character.h"

namespace dnd_rogue::core::models {

TEST(CharacterTest, Initialization) {
  Character c(CharacterClass::Wizard);
  EXPECT_EQ(c.GetClass(), CharacterClass::Wizard);
}

TEST(CharacterClassTest, Helpers) {
  EXPECT_EQ(GetCharacterClassName(CharacterClass::Sorcerer), "Sorcerer");

  glm::vec4 fighterColor = GetCharacterClassColor(CharacterClass::Fighter);
  EXPECT_FLOAT_EQ(fighterColor.r, 0.7f);
}

} // namespace dnd_rogue::core::models
