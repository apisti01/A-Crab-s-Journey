//
// Created by apisti01 on 04/08/22.
//

#ifndef MAIN_CPP_DEFENSIVEMELEEENEMY_H
#define MAIN_CPP_DEFENSIVEMELEEENEMY_H

#include "Enemy.h"

/*
 * stays still in place until the player moves too close, then it chases and attacks him until the end of its range, then it returns to its original position
 */
class DefensiveMeleeEnemy : public Enemy{
public:
    DefensiveMeleeEnemy(std::string name, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
                        float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                        float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, float triggerRange);
    ~DefensiveMeleeEnemy() override = default;

    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool clicked) override;

    void dropItems() override;
private:
    // range which, if the player is inside, the enemy is triggered and tries to chase and attack him
    float triggerRange;

    float origPosX;
    float origPosY;
};


#endif //MAIN_CPP_DEFENSIVEMELEEENEMY_H
