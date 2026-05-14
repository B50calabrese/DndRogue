#include <gtest/gtest.h>
#include "core/run_state.h"
#include "core/card.h"
#include "core/commander.h"

using namespace dnd_rogue::core;

TEST(RunStateTest, Initialization) {
  RunState& run_state = RunState::Get();
  run_state.Initialize(12345);

  EXPECT_EQ(run_state.GetSeed(), 12345);
  EXPECT_EQ(run_state.GetGold(), 0);
  EXPECT_TRUE(run_state.GetCollection().empty());
  EXPECT_TRUE(run_state.GetDeck().empty());
  EXPECT_TRUE(run_state.GetCommanders().empty());
}

TEST(RunStateTest, GoldManagement) {
  RunState& run_state = RunState::Get();
  run_state.Initialize(12345);

  run_state.SetGold(100);
  EXPECT_EQ(run_state.GetGold(), 100);

  run_state.AddGold(50);
  EXPECT_EQ(run_state.GetGold(), 150);
}

TEST(RunStateTest, CardAndCommanderManagement) {
  RunState& run_state = RunState::Get();
  run_state.Initialize(12345);

  Card strike = {"strike", "Strike"};
  run_state.AddToCollection(strike);
  run_state.AddToDeck(strike);

  Commander king = {"king", "King"};
  run_state.AddCommander(king);

  EXPECT_EQ(run_state.GetCollection().size(), 1);
  EXPECT_EQ(run_state.GetCollection()[0].id, "strike");

  EXPECT_EQ(run_state.GetDeck().size(), 1);
  EXPECT_EQ(run_state.GetDeck()[0].id, "strike");

  EXPECT_EQ(run_state.GetCommanders().size(), 1);
  EXPECT_EQ(run_state.GetCommanders()[0].id, "king");
}

TEST(RunStateTest, Serialization) {
  RunState& run_state = RunState::Get();
  run_state.Initialize(98765);
  run_state.SetGold(500);

  Card c1 = {"c1", "Card 1"};
  Card c2 = {"c2", "Card 2"};
  run_state.AddToCollection(c1);
  run_state.AddToCollection(c2);
  run_state.AddToDeck(c1);

  Commander cmd = {"cmd1", "Commander 1"};
  run_state.AddCommander(cmd);

  std::vector<uint8_t> data = run_state.Serialize();

  // Create a new state or reset and deserialize
  run_state.Initialize(0);
  EXPECT_EQ(run_state.GetSeed(), 0);
  EXPECT_EQ(run_state.GetGold(), 0);

  run_state.Deserialize(data);

  EXPECT_EQ(run_state.GetSeed(), 98765);
  EXPECT_EQ(run_state.GetGold(), 500);

  ASSERT_EQ(run_state.GetCollection().size(), 2);
  EXPECT_EQ(run_state.GetCollection()[0].id, "c1");
  EXPECT_EQ(run_state.GetCollection()[1].id, "c2");

  ASSERT_EQ(run_state.GetDeck().size(), 1);
  EXPECT_EQ(run_state.GetDeck()[0].id, "c1");

  ASSERT_EQ(run_state.GetCommanders().size(), 1);
  EXPECT_EQ(run_state.GetCommanders()[0].id, "cmd1");
}
