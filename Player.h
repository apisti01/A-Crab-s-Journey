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


    // if weapon is ranged create bullet, if melee find the first in range enemy and gives it damages
    void attack(std::list<Enemy> enemyList);

    // TODO
    bool checkEnemy(const Enemy& enemy);

    // Take a Wearable and puts it on, return the item wore before
    std::unique_ptr<Wearable> wearItem(std::unique_ptr<Wearable> item);

    // TAke a Weapon and puts it on, return the weapon wielded before
    std::unique_ptr<Weapon> changeWeapon(std::unique_ptr<Weapon> weapon1);

private:
    std::string namePlayer;

    // Specification about the starting statistics
    CrabSpecie crabSpecie;

    int coins;

    // Wearable on the player
    std::unique_ptr<Wearable> hat = nullptr;
    std::unique_ptr<Wearable> shield = nullptr;
    std::unique_ptr<Wearable> shell = nullptr;

};


#endif //MAIN_CPP_PLAYER_H
