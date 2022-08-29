//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include <list>

#include "Game.h"
#include "GameCharacter.h"
#include "Enemy_source_files/Enemy.h"
#include "Wearable.h"
#include "Enemy_source_files/StaticRangedEnemy.h"
#include "Weapon.h"
#include "RangedWeapon.h"
#include "FloorMap.h"

enum class CrabSpecie {
    BrownCrab,
    FiddlerCrab,
    TriangleTannerCrab,
    AsianGreatPaddle
};

class Player : public GameCharacter {
public:
    // Constructor and Destructor
    Player(int characterIndex, std::string name, CrabSpecie crabSpecie, const sf::Texture &texture, Collider collider,
           std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed, float maxSpeed, float armor,
           float maxArmor, float strength, float maxStrength);

    ~Player() override = default;

    void update(int deltaTime, FloorMap *floor, bool clicked) override;

    void attack(FloorMap *floor, bool clicked) override;

    // take a Wearable and puts it on, return the item wore before
    std::unique_ptr<Wearable> wearItem(std::unique_ptr<Wearable> item);

    // take a Weapon and puts it on, return the weapon wielded before
    std::unique_ptr<Weapon> changeWeapon(std::unique_ptr<Weapon> weapon1);

    int characterIndex;
private:
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

    // change room status
    void checkCageStatus(FloorMap *floor);

    // modify the statistics of the player given the object
    void modifyStatistics(Wearable *item, bool wore);
};


#endif //MAIN_CPP_PLAYER_H
