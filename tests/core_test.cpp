#include <gtest/gtest.h>

#include <vector>

#include "core/models/character.h"
#include "core/session.h"

using namespace dnd_rogue::core;
using namespace dnd_rogue::core::models;

TEST(CharacterTest, Initialization) {
  Character c(CharacterClass::Wizard);
  EXPECT_EQ(c.GetClass(), CharacterClass::Wizard);
}

TEST(SessionTest, RunInitialization) {
  std::vector<CharacterClass> classes = {
      CharacterClass::Fighter, CharacterClass::Rogue, CharacterClass::Cleric,
      CharacterClass::Wizard};

  Session::Get().InitRun(classes);
  const auto& party = Session::Get().GetParty();

  ASSERT_EQ(party.size(), 4);
  EXPECT_EQ(party[0].GetClass(), CharacterClass::Fighter);
  EXPECT_EQ(party[1].GetClass(), CharacterClass::Rogue);
  EXPECT_EQ(party[2].GetClass(), CharacterClass::Cleric);
  EXPECT_EQ(party[3].GetClass(), CharacterClass::Wizard);
}

TEST(CharacterClassTest, Helpers) {
  EXPECT_EQ(GetCharacterClassName(CharacterClass::Sorcerer), "Sorcerer");

  glm::vec4 fighterColor = GetCharacterClassColor(CharacterClass::Fighter);
  EXPECT_FLOAT_EQ(fighterColor.r, 0.7f);
}
