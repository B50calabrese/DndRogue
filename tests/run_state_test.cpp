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
}

TEST(RunStateTest, Serialization) {
  RunState& state = RunState::Get();
  uint64_t expected_seed = 987654321ULL;
  state.Initialize(expected_seed);

  std::vector<uint8_t> data = state.Serialize();
  EXPECT_FALSE(data.empty());

  // Reset seed and deserialize
  state.Initialize(0);
  EXPECT_EQ(state.GetSeed(), 0);

  state.Deserialize(data);
  EXPECT_EQ(state.GetSeed(), expected_seed);
}

}  // namespace dnd_rogue::core
