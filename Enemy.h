//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_ENEMY_H
#define MAIN_CPP_ENEMY_H

#include "GameCharacter.h"

class Player;

class Enemy : public GameCharacter{
public:
    // TODO Constructor and Destructor

    ~Enemy() override = default;

    virtual void chase(Player hero) = 0;

    virtual void dropItems() = 0;

protected:
    // Stuff dropped when killed
    float XpReward;
    int coinsDropped;
    int pearlsDropped;

};


#endif //MAIN_CPP_ENEMY_H
