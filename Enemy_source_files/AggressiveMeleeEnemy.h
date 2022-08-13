//
// Created by apisti01 on 03/08/22.
//

#ifndef MAIN_CPP_AGGRESSIVEMELEEENEMY_H
#define MAIN_CPP_AGGRESSIVEMELEEENEMY_H

#include "Enemy.h"
/*
 * search for the player, chase him and attack him at will
 */
class AggressiveMeleeEnemy : public Enemy{
public:
    AggressiveMeleeEnemy(std::string name, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
                         float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                         float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, float triggerRange);
    ~AggressiveMeleeEnemy() override = default;

    void dropItems() override;

    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool triggered) override;
private:
    // range in which the enemy tries to attack the player, only to not kill other enemies when far from the player
    float triggerRange;
};


#endif //MAIN_CPP_AGGRESSIVEMELEEENEMY_H
