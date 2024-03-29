//
// Created by apisti01 on 15/07/22.
//

#include "gtest/gtest.h"

#include "../Player.h"
#include "../Player.cpp"
#include "../GameCharacter.h"
#include "../GameCharacter.cpp"
#include "../MeleeWeapon.h"
#include "../RangedWeapon.h"


class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        Test::SetUp();
        player.setPosition(0, 0);
    }

    Collider collider;
    Player player {0, "test", CrabSpecie::BrownCrab, sf::Texture(), collider, nullptr, 10, 10, 10, 10, 10, 10, 10, 10};
};

TEST_F(PlayerTest, DefaultConstructor) {
    ASSERT_FALSE(player.getWeapon());

    ASSERT_EQ(player.getName(), "test");

    ASSERT_EQ(player.getCoins(), 0);

    ASSERT_EQ(player.getHp(), 10);
    ASSERT_EQ(player.getMaxHp(), 10);

    ASSERT_FLOAT_EQ(player.getArmor(), 10);
    ASSERT_FLOAT_EQ(player.getMaxArmor(), 10);

    ASSERT_FLOAT_EQ(player.getStrength(), 10);
    ASSERT_FLOAT_EQ(player.getMaxStrength(), 10);

    ASSERT_EQ(player.getSpeed(), 10);
    ASSERT_EQ(player.getMaxSpeed(), 10);
}

TEST_F(PlayerTest, BasicInteractions) {
    // check receive coins
    player.receiveCoins(12);
    ASSERT_EQ(player.getCoins(), 12);

    // check damage received
    player.receiveDamage(5);
    ASSERT_EQ(player.getHp(), 10);
}

TEST_F(PlayerTest, Weapon) {
    // create new melee weapon
    std::unique_ptr<Weapon> weapon1 = std::make_unique<MeleeWeapon>(MeleeWeaponType::NaturalWeapon, "test");

    // insert the new weapon, tmp should be null cause player did not have any weapon before
    auto tmp = player.changeWeapon(std::move(weapon1));

    // check which pointer does contain a weapon
    ASSERT_EQ(weapon1, nullptr);
    ASSERT_EQ(tmp, nullptr);
    ASSERT_TRUE(player.getWeapon());

    // create a new ranged weapon
    std::unique_ptr<Weapon> weapon2 = std::make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon,"test");

    // put the new weapon on, tmp takes the old melee weapon
    tmp = player.changeWeapon(std::move(weapon2));

    // check which pointer does contain a weapon
    ASSERT_TRUE(tmp);
    ASSERT_EQ(weapon2, nullptr);
    ASSERT_TRUE(player.getWeapon());

}
