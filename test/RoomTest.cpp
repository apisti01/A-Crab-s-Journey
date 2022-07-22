//
// Created by longo on 17/07/2022.
//

#include "gtest/gtest.h"

#include "../Room.h"
#include "../Room.cpp"

class RoomTest : public ::testing::Test {
protected:
    void SetUp() override {
        Test::SetUp();
    }

    Room room {0, 0, 1920, 1080};
};

TEST_F(RoomTest, DefaultConstructor) {
    ASSERT_EQ(room.getPosX(), 0);
    ASSERT_EQ(room.getPosY(), 0);

    ASSERT_FALSE(room.getStartRoom());
    ASSERT_FALSE(room.getBossRoom());
    ASSERT_FALSE(room.getShopRoom());

    ASSERT_FALSE(room.getCage());

    ASSERT_EQ(room.getXpReward(), 0);
}

TEST_F(RoomTest, getterAndSetter) {
    room.setPosX(1);
    ASSERT_EQ(room.getPosX(), 1);

    room.setPosY(2);
    ASSERT_EQ(room.getPosY(), 2);

    room.setStartRoom(true);
    ASSERT_TRUE(room.getStartRoom());
    room.setBossRoom(true);
    ASSERT_TRUE(room.getBossRoom());
    room.setShopRoom(true);
    ASSERT_TRUE(room.getShopRoom());

    room.setCage(true);
    ASSERT_TRUE(room.getCage());

    room.setXpReward(10);
    ASSERT_EQ(room.getXpReward(), 10);
}