//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include <list>

#include "GameCharacter.h"
#include "Enemy.h"
#include "Wearable.h"
#include "StaticRangedEnemy.h"
#include "Weapon.h"
#include "FloorMap.h"

enum class CrabSpecie {
    BrownCrab,
    AsianPaddleCrab,
    TriangleTannerCrab,
    FiddlerCrab
};

class Player : public GameCharacter {
public:
    // Constructor and Destructor
    Player(std::string name, CrabSpecie crabSpecie, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> Weapon,
           float hp = 8, float maxHp = 10, float speed = 2, float maxSpeed = 3, float armor = 0.2,
           float maxArmor = 0.5, float strength = 1.2, float maxStrength = 2, int coins = 0);
    ~Player() override = default;

    void update(int deltaTime, FloorMap *floor) override;

    void attack(FloorMap *floor, float bulletAngle) override;

    // take a Wearable and puts it on, return the item wore before
    std::unique_ptr<Wearable> wearItem(std::unique_ptr<Wearable> item);

    // take a Weapon and puts it on, return the weapon wielded before
    std::unique_ptr<Weapon> changeWeapon(std::unique_ptr<Weapon> weapon1);

private:
    // name of the crab specie
    std::string namePlayer;

    // Specification about the starting statistics
    CrabSpecie crabSpecie;

    // wearable on the player
    std::unique_ptr<Wearable> hat = nullptr;
    std::unique_ptr<Wearable> shield = nullptr;
    std::unique_ptr<Wearable> shell = nullptr;

    // move player with user input
    sf::Vector2f getKeyboardInput(int deltaTime, FloorMap *floor);

    // change angle of the player based on mouse movement
    float getMouseInput(int deltaTime);

    // change room if a door is walked
    void changeRoom(FloorMap *floor);
};


#endif //MAIN_CPP_PLAYER_H
