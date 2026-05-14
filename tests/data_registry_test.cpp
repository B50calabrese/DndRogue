#include <gtest/gtest.h>
#include "core/data_registry.h"
#include "engine/util/logger.h"

using namespace dnd_rogue::core;

class DataRegistryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Assets are in the build directory usually,
        // but for this test we'll use the source assets
        // since we just created them.
    }
};

TEST_F(DataRegistryTest, LoadCardsAndCommanders) {
    DataRegistry& registry = DataRegistry::Get();
    // Assuming we are running from build/
    registry.LoadAll("../assets");

    const Card* strike = registry.GetCard("strike");
    ASSERT_NE(strike, nullptr);
    EXPECT_EQ(strike->name, "Strike");

    const Card* defend = registry.GetCard("defend");
    ASSERT_NE(defend, nullptr);
    EXPECT_EQ(defend->name, "Defend");

    const Commander* king = registry.GetCommander("warrior_king");
    ASSERT_NE(king, nullptr);
    EXPECT_EQ(king->name, "Warrior King");
}
