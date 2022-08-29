//
// Created by apisti01 on 03/08/22.
//

#include "AggressiveMeleeEnemy.h"
#include "../Player.h"
#include "../Weapon.h"

AggressiveMeleeEnemy::AggressiveMeleeEnemy(std::string name, const sf::Texture &texture, Collider collider,
                                           std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed,
                                           float maxSpeed, float armor, float maxArmor, float strength,
                                           float maxStrength, float XpReward, int coinsDropped, int pearlsDropped,
                                           int attackTimer, float triggerRange)
        : Enemy(std::move(name), texture, std::move(collider), std::move(weapon), hp, maxHp, speed, maxSpeed, armor,
                maxArmor, strength, maxStrength, XpReward, coinsDropped, pearlsDropped, attackTimer),
                triggerRange(triggerRange) {
}

sf::Vector2f AggressiveMeleeEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) {
    // position of the player
    auto movement = sf::Vector2f { hero->getPosX(), hero->getPosY() };

    // coordinates relative to the position of the enemy
    movement.x -= getPosX();
    movement.y -= getPosY();

    // variation in radians of the facing angle
    deltaAngle = atan2f(movement.y, movement.x) - getAngle();

    // normalization
    float norm = sqrtf(powf(movement.x, 2) + powf(movement.y, 2));
    if (norm != 0) {
        movement.x = movement.x / norm;
        movement.y = movement.y / norm;
    }

    // attacking only if the player is near the enemy
    if (norm < triggerRange)
        triggered = true;
    else
        triggered = false;

    // the actual movement
    movement.x = movement.x * speed * Game::getInstance()->lenUnit * static_cast<float>(deltaTime) / pow(10, 6);
    movement.y = movement.y * speed * Game::getInstance()->lenUnit * static_cast<float>(deltaTime) / pow(10, 6);

    return movement;
}

void AggressiveMeleeEnemy::attack(FloorMap *floor, bool triggered) {
    // attack with the melee weapon
    if (triggered)
        weapon->useWeapon(floor, this);
}

void AggressiveMeleeEnemy::dropItems() {
    // TODO: random drop of items
}

