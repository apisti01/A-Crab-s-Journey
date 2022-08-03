//
// Created by apisti01 on 13/07/22.
//

#ifndef MAIN_CPP_STATICRANGEDENEMY_H
#define MAIN_CPP_STATICRANGEDENEMY_H

#include "Enemy.h"

class StaticRangedEnemy : Enemy {
public:
    StaticRangedEnemy();
    ~StaticRangedEnemy() override = default;

private:
    sf::Vector2f chase(const Player *hero, float &deltaAngle) override;

    void attack(FloorMap *floor, float bulletAngle, bool clicked) override;

public:
    void dropItems() override;
};


#endif //MAIN_CPP_STATICRANGEDENEMY_H
