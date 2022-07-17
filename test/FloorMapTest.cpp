//
// Created by longo on 17/07/2022.
//

#include "gtest/gtest.h"

#include "../FloorMap.h"
#include "../FloorMap.cpp"

class FloorMapTest : public ::testing::Test {
protected:
    void SetUp() override {
        Test::SetUp();
    }

    FloorMap floorMap {1};
};

TEST_F(FloorMapTest, DefaultConstructor) {
    ASSERT_EQ(floorMap.getLevel(), 1);
    ASSERT_TRUE(floorMap.getNumRooms());
    ASSERT_TRUE(floorMap.getLongestPathLength());

    ASSERT_TRUE(floorMap.startRoomIndex);
    ASSERT_TRUE(floorMap.endRoomIndex);
}

TEST_F(FloorMapTest, getterAndSetter) {
    floorMap.setLevel(2);
    ASSERT_EQ(floorMap.getLevel(), 2);

    floorMap.setNumRooms(10);
    ASSERT_EQ(floorMap.getNumRooms(), 10);

    floorMap.setLongestPathLength(20);
    ASSERT_EQ(floorMap.getLongestPathLength(), 20);
}