//
// Created by apisti01 on 04/08/22.
//

#ifndef MAIN_CPP_CHASINGRANGEDENEMY_H
#define MAIN_CPP_CHASINGRANGEDENEMY_H

#include "Enemy.h"

class ChasingRangedEnemy : public Enemy{
public:
    ChasingRangedEnemy(int id, std::string name, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
                       float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                       float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, int attackTimer,
                       float triggerRange);
    ~ChasingRangedEnemy() override = default;

    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool triggered) override;

    void dropItems() override;

private:
    float triggerRange;
};


#endif //MAIN_CPP_CHASINGRANGEDENEMY_H
