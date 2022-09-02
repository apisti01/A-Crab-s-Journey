//
// Created by apisti01 on 04/08/22.
//

#include "ChasingRangedEnemy.h"
#include "../Player.h"

ChasingRangedEnemy::ChasingRangedEnemy(int id, std::string name, const sf::Texture &texture, Collider collider,
                                       std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed,
                                       float maxSpeed, float armor, float maxArmor, float strength, float maxStrength,
                                       float XpReward, int coinsDropped, int pearlsDropped, int attackTimer,
                                       float triggerRange) :
                                       Enemy(id, std::move(name), texture, std::move(collider),
                                             std::move(weapon), hp, maxHp, speed, maxSpeed, armor, maxArmor,
                                             strength, maxStrength, XpReward, coinsDropped, pearlsDropped, attackTimer),
                                             triggerRange(triggerRange) {
}

sf::Vector2f ChasingRangedEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) {
    // position of the player
    auto movement = sf::Vector2f { hero->getPosX(), hero->getPosY() };

    // coordinates relative to the position of the enemy
    movement.x -= getPosX();
    movement.y -= getPosY();

    // normalization
    float distance = sqrtf(powf(movement.x, 2) + powf(movement.y, 2));

    // variation in radians of the facing angle
    deltaAngle = atan2f(movement.y, movement.x) - getAngle();

    // if the enemy is too far from the player
    if (distance > triggerRange) {
        // normalization
        if (distance != 0) {
            movement.x = movement.x / distance;
            movement.y = movement.y / distance;
        }

        // it does not attack
        triggered = false;

        // it moves to come near the player
        movement.x = movement.x * speed * Game::getInstance()->u * static_cast<float>(deltaTime) / pow(10, 6);
        movement.y = movement.y * speed * Game::getInstance()->u * static_cast<float>(deltaTime) / pow(10, 6);
    }
    // if the enemy is near enough
    else {
        // stand still and does not attack
        movement = sf::Vector2f {0.f, 0.f};
        triggered = true;
    }

    return movement;
}

void ChasingRangedEnemy::attack(FloorMap *floor, bool triggered) {
    // when the player is close attacks with ranged weapon
    if (triggered)
        weapon->useWeapon(floor, this);
}

void ChasingRangedEnemy::dropItems() {
    // TODO random drop of items
}
