//
// Created by longo on 17/07/2022.
//

#include "gtest/gtest.h"

#include "../Obstacle.h"
#include "../Obstacle.cpp"
#include "../Collider.h"

class ObstacleTest : public ::testing::Test {
protected:
    void SetUp() override {
        Test::SetUp();
    }

    sf::Texture texture;
    Collider collider;
    Obstacle obstacle {texture, collider, 0, 0, 50, 50};
};

TEST_F(ObstacleTest, DefaultConstructor) {
    ASSERT_EQ(obstacle.getPosX(), 0);
    ASSERT_EQ(obstacle.getPosY(), 0);
    ASSERT_EQ(obstacle.getWidth(), 50);
    ASSERT_EQ(obstacle.getHeight(), 50);

    ASSERT_EQ(obstacle.getDamage(), 0);
}

TEST_F(ObstacleTest, getterAndSetter) {
    obstacle.setPosX(10);
    ASSERT_EQ(obstacle.getPosX(), 10);
    obstacle.setPosY(30);
    ASSERT_EQ(obstacle.getPosY(), 30);

    obstacle.setWidth(100);
    ASSERT_EQ(obstacle.getWidth(), 100);
    obstacle.setHeight(150);
    ASSERT_EQ(obstacle.getHeight(), 150);

    obstacle.setDamage(2);
    ASSERT_EQ(obstacle.getDamage(), 2);
}