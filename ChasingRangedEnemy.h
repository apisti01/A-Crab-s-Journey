//
// Created by apisti01 on 04/08/22.
//

#ifndef MAIN_CPP_CHASINGRANGEDENEMY_H
#define MAIN_CPP_CHASINGRANGEDENEMY_H

#include "Enemy.h"

/*
 * if the player comes too close the enemy will chase him and attack him from distance, when the player will escape from the range of the enemy
 * it will stop and remain in the place it is
 */
class ChasingRangedEnemy : public Enemy{
public:
    ~ChasingRangedEnemy() override = default;

    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool triggered) override;

    void dropItems() override;

private:
    float triggerRange;
};


#endif //MAIN_CPP_CHASINGRANGEDENEMY_H
