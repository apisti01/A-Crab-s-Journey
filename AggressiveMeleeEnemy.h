//
// Created by apisti01 on 03/08/22.
//

#ifndef MAIN_CPP_AGGRESSIVEMELEEENEMY_H
#define MAIN_CPP_AGGRESSIVEMELEEENEMY_H

#include "Enemy.h"

class AggressiveMeleeEnemy : public Enemy{
public:
    ~AggressiveMeleeEnemy() override = default;

    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime) override;

    void attack(FloorMap *floor, bool clicked) override;
};


#endif //MAIN_CPP_AGGRESSIVEMELEEENEMY_H
