#include <gtest/gtest.h>
#include "core/overworld/room_generator.h"
#include "core/overworld/map_config.h"
#include "core/overworld/map_data.h"

using namespace dnd_rogue::core::overworld;

TEST(RoomGeneratorTest, BasicGeneration) {
    RoomGenerator generator;
    MapConfig config;
    config.width = 20;
    config.height = 20;

    auto map = generator.Generate(config);

    EXPECT_NE(map, nullptr);
    EXPECT_EQ(map->width(), 20);
    EXPECT_EQ(map->height(), 20);

    // Check if player position is within bounds
    glm::ivec2 p_pos = map->player_pos();
    EXPECT_GE(p_pos.x, 0);
    EXPECT_LT(p_pos.x, 20);
    EXPECT_GE(p_pos.y, 0);
    EXPECT_LT(p_pos.y, 20);
}

TEST(RoomGeneratorTest, Walkability) {
    RoomGenerator generator;
    MapConfig config;
    auto map = generator.Generate(config);

    // Player should be on a walkable tile
    EXPECT_TRUE(map->IsWalkable(map->player_pos().x, map->player_pos().y));
}
