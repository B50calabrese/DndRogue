#include <gtest/gtest.h>
#include "core/run_state.h"

namespace dnd_rogue::core {

TEST(RunStateTest, SingletonInstance) {
  RunState& instance1 = RunState::Get();
  RunState& instance2 = RunState::Get();
  EXPECT_EQ(&instance1, &instance2);
}

TEST(RunStateTest, Initialization) {
  RunState& state = RunState::Get();
  uint64_t expected_seed = 12345ULL;
  state.Initialize(expected_seed);
  EXPECT_EQ(state.GetSeed(), expected_seed);
  EXPECT_EQ(state.GetGold(), 100);
  ASSERT_EQ(state.GetCharacters().size(), 1);
  EXPECT_EQ(state.GetCharacters()[0].name, "Test Character");
  ASSERT_EQ(state.GetCombatCards().size(), 1);
  EXPECT_EQ(state.GetCombatCards()[0].name, "Test Card");
  ASSERT_EQ(state.GetItems().size(), 1);
  EXPECT_EQ(state.GetItems()[0].name, "Test Item");
}

TEST(RunStateTest, GoldModification) {
  RunState& state = RunState::Get();
  state.Initialize(0);
  state.SetGold(500);
  EXPECT_EQ(state.GetGold(), 500);
  state.AddGold(100);
  EXPECT_EQ(state.GetGold(), 600);
  state.AddGold(-200);
  EXPECT_EQ(state.GetGold(), 400);
}

TEST(RunStateTest, CollectionModification) {
  RunState& state = RunState::Get();
  state.Initialize(0);

  state.AddCharacter({"Warrior"});
  EXPECT_EQ(state.GetCharacters().size(), 2);  // 1 default + 1 added
  EXPECT_EQ(state.GetCharacters()[1].name, "Warrior");

  state.AddCombatCard({"Slash"});
  EXPECT_EQ(state.GetCombatCards().size(), 2);
  EXPECT_EQ(state.GetCombatCards()[1].name, "Slash");

  state.AddItem({"Potion"});
  EXPECT_EQ(state.GetItems().size(), 2);
  EXPECT_EQ(state.GetItems()[1].name, "Potion");
}

TEST(RunStateTest, Serialization) {
  RunState& state = RunState::Get();
  uint64_t expected_seed = 987654321ULL;
  state.Initialize(expected_seed);
  state.SetGold(1234);
  state.AddCharacter({"Archer"});
  state.AddCombatCard({"Shoot"});
  state.AddItem({"Bow"});

  std::vector<uint8_t> data = state.Serialize();
  EXPECT_FALSE(data.empty());

  // Reset and deserialize
  state.Initialize(0);
  EXPECT_EQ(state.GetSeed(), 0);
  EXPECT_EQ(state.GetGold(), 100);

  state.Deserialize(data);
  EXPECT_EQ(state.GetSeed(), expected_seed);
  EXPECT_EQ(state.GetGold(), 1234);
  ASSERT_EQ(state.GetCharacters().size(), 2);
  EXPECT_EQ(state.GetCharacters()[0].name, "Test Character");
  EXPECT_EQ(state.GetCharacters()[1].name, "Archer");
  ASSERT_EQ(state.GetCombatCards().size(), 2);
  EXPECT_EQ(state.GetCombatCards()[0].name, "Test Card");
  EXPECT_EQ(state.GetCombatCards()[1].name, "Shoot");
  ASSERT_EQ(state.GetItems().size(), 2);
  EXPECT_EQ(state.GetItems()[0].name, "Test Item");
  EXPECT_EQ(state.GetItems()[1].name, "Bow");
}

}  // namespace dnd_rogue::core
