//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_ENEMY_H
#define MAIN_CPP_ENEMY_H

#include "GameCharacter.h"

class Player;

class Enemy : public GameCharacter{
public:
    // Constructor and Destructor
    Enemy(std::string name, std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed, float maxSpeed,
          float armor, float maxArmor, float strength, float maxStrength, float xpReward, int coinsDropped, int pearlsDropped);
    ~Enemy() override = default;

    // move towards the player
    virtual void chase(const Player& hero) = 0;


    // drop items when killed
    virtual void dropItems() = 0;

protected:
    // Stuff dropped when killed
    float XpReward;
    int coinsDropped;
    int pearlsDropped;
};


#endif //MAIN_CPP_ENEMY_H
