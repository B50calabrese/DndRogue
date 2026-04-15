#include <gtest/gtest.h>
#include "core/overworld/room_generator.h"
#include "core/overworld/map_config.h"
#include "core/overworld/map_data.h"
#include "core/overworld/overworld_utils.h"

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

TEST(OverworldUtilsTest, CameraCalculation) {
    glm::vec2 target = { 500, 500 };
    glm::vec2 drawable = { 1000, 1000 };
    glm::vec2 map = { 2000, 2000 };

    // Center of drawable should result in (0,0) camera
    glm::vec3 cam_pos = OverworldUtils::CalculateCameraPosition(target, drawable, map);
    EXPECT_FLOAT_EQ(cam_pos.x, 0.0f);
    EXPECT_FLOAT_EQ(cam_pos.y, 0.0f);

    // Target at 1500, 1500 should result in (1000, 1000) camera
    target = { 1500, 1500 };
    cam_pos = OverworldUtils::CalculateCameraPosition(target, drawable, map);
    EXPECT_FLOAT_EQ(cam_pos.x, 1000.0f);
    EXPECT_FLOAT_EQ(cam_pos.y, 1000.0f);

    // Clamping: Target at 2000, 2000 should still result in (1000, 1000) camera
    target = { 2000, 2000 };
    cam_pos = OverworldUtils::CalculateCameraPosition(target, drawable, map);
    EXPECT_FLOAT_EQ(cam_pos.x, 1000.0f);
    EXPECT_FLOAT_EQ(cam_pos.y, 1000.0f);
}
