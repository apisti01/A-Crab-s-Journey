//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include <list>

#include "GameCharacter.h"
#include "Enemy.h"
#include "Wearable.h"

enum class CrabSpecie{
    BrownCrab,
    AsianPaddleCrab,
    TriangleTannerCrab,
    FiddlerCrab
};

class Player : public GameCharacter{
public:
    // Constructor and Destructor
    Player(std::string name, float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor,
           float strength, float maxStrength, std::unique_ptr<Weapon> Weapon, std::string namePlayer,
           CrabSpecie crabSpecie, int coins);
    ~Player() override = default;

    // if weapon is ranged create bullet, if melee find the first in range enemy and gives it damages
    void attack(std::list<Enemy> enemyList);

    // TODO: write definition for the selection of hit enemy
    bool checkEnemy(const Enemy& enemy);

    // take a Wearable and puts it on, return the item wore before
    std::unique_ptr<Wearable> wearItem(std::unique_ptr<Wearable> item);

    // take a Weapon and puts it on, return the weapon wielded before
    std::unique_ptr<Weapon> changeWeapon(std::unique_ptr<Weapon> weapon1);

private:
    // name of the crab specie
    std::string namePlayer;

    // Specification about the starting statistics
    CrabSpecie crabSpecie;

    // coin owned
    int coins;

    // wearable on the player
    std::unique_ptr<Wearable> hat = nullptr;
    std::unique_ptr<Wearable> shield = nullptr;
    std::unique_ptr<Wearable> shell = nullptr;
};


#endif //MAIN_CPP_PLAYER_H
