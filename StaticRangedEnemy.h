//
// Created by apisti01 on 13/07/22.
//

#ifndef MAIN_CPP_STATICRANGEDENEMY_H
#define MAIN_CPP_STATICRANGEDENEMY_H

#include "Enemy.h"
/*
 * stays still and attack the player at will,
 */
class StaticRangedEnemy : Enemy {
public:
    StaticRangedEnemy();
    ~StaticRangedEnemy() override = default;

    void dropItems() override;

private:
    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool clicked) override;
};


#endif //MAIN_CPP_STATICRANGEDENEMY_H
