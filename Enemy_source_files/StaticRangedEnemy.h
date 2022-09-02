//
// Created by apisti01 on 13/07/22.
//

#ifndef MAIN_CPP_STATICRANGEDENEMY_H
#define MAIN_CPP_STATICRANGEDENEMY_H

#include "Enemy.h"
/*
 * stays still and attack the player at will,
 */
class StaticRangedEnemy :  public Enemy {
public:
    StaticRangedEnemy(int id, std::string name, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
                      float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                      float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, int attackTimer);
    ~StaticRangedEnemy() override = default;

    void dropItems() override;

private:
    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool clicked) override;
};


#endif //MAIN_CPP_STATICRANGEDENEMY_H
