//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_ENEMY_H
#define MAIN_CPP_ENEMY_H

#include "../GameCharacter.h"

class Player;

class Enemy : public GameCharacter {
public:
    // Constructor and Destructor
    Enemy(int id, std::string name, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
          float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
          float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, int attackTimer, float units);
    ~Enemy() override = default;

    void update(int deltaTime, FloorMap *floor, bool triggered, sf::RenderWindow &window) override;

    // movement and facing of the enemy1, return the movement
    virtual sf::Vector2f chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) = 0;

    // attack the player on the conditions of the enemy1
    void attack(FloorMap *floor, bool triggered) override = 0;

    // drop items when killed
    virtual void dropItems() = 0;

    int getId() const{
        return id;
    }

private:
    int id;

    // Stuff dropped when killed
    float XpReward;
    int coinsDropped;
    int pearlsDropped;

    int attackTimer;
    int clock;
};


#endif //MAIN_CPP_ENEMY_H
