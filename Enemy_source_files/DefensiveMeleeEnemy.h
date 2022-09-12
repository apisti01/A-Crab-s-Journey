//
// Created by apisti01 on 04/08/22.
//

#ifndef MAIN_CPP_DEFENSIVEMELEEENEMY_H
#define MAIN_CPP_DEFENSIVEMELEEENEMY_H

#include "Enemy.h"

class DefensiveMeleeEnemy : public Enemy {
public:
    DefensiveMeleeEnemy(int id, std::string name, const sf::Texture &texture, Collider collider, std::unique_ptr<Weapon> weapon,
                        float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                        float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, int attackTimer,
                        float triggerRange, float units);

    ~DefensiveMeleeEnemy() override = default;

    sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) override;

    void attack(FloorMap *floor, bool triggered) override;

    void dropItems() override;

    // this function is overridden to permit to save the original position of the character in its attributes
    void setPosition(sf::Vector2f pos) override {
        collider.setPosition(pos);
        sprite.setPosition(pos);
        origPos = pos;
    }

private:
    // range which, if the player is inside, the enemy is triggered and tries to chase and attack him
    float triggerRange;

    sf::Vector2f origPos;
};


#endif //MAIN_CPP_DEFENSIVEMELEEENEMY_H
