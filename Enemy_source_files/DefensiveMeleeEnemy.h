//
// Created by apisti01 on 04/08/22.
//

#ifndef MAIN_CPP_DEFENSIVEMELEEENEMY_H
#define MAIN_CPP_DEFENSIVEMELEEENEMY_H

#include "Enemy.h"

/*
 * stays still in place until the player moves too close, then it chases and attacks him until the end of its range, then it returns to its original position
 */
class DefensiveMeleeEnemy : public Enemy {
public:
    DefensiveMeleeEnemy(int id, std::string name, const sf::Texture &texture, Collider collider, std::unique_ptr<Weapon> weapon,
                        float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                        float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, int attackTimer,
                        float triggerRange);

    ~DefensiveMeleeEnemy() override = default;

    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool triggered) override;

    void dropItems() override;

    // this function is overridden to permit to save the original position of the character in its attributes
    void setPosition(float x, float y) override{
        collider.setPosX(x);
        collider.setPosY(y);
        sprite.setPosition(sf::Vector2f(x, y));
        origPosX = x;
        origPosY = y;
    }

private:
    // range which, if the player is inside, the enemy is triggered and tries to chase and attack him
    float triggerRange;

    float origPosX;
    float origPosY;
};


#endif //MAIN_CPP_DEFENSIVEMELEEENEMY_H
