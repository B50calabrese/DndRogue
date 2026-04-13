#include <gtest/gtest.h>
#include "core/session.h"
#include <vector>

namespace dnd_rogue::core {

TEST(SessionTest, RunInitialization) {
  std::vector<models::CharacterClass> classes = {
      models::CharacterClass::Fighter, models::CharacterClass::Rogue,
      models::CharacterClass::Cleric, models::CharacterClass::Wizard};

  Session::Get().InitRun(classes);
  const auto& party = Session::Get().GetParty();

  ASSERT_EQ(party.size(), 4);
  EXPECT_EQ(party[0].GetClass(), models::CharacterClass::Fighter);
  EXPECT_EQ(party[1].GetClass(), models::CharacterClass::Rogue);
  EXPECT_EQ(party[2].GetClass(), models::CharacterClass::Cleric);
  EXPECT_EQ(party[3].GetClass(), models::CharacterClass::Wizard);
}

} // namespace dnd_rogue::core
