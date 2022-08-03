//
// Created by apisti01 on 03/08/22.
//

#include "AggressiveMeleeEnemy.h"
#include "Player.h"

sf::Vector2f AggressiveMeleeEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime) {
    // position of the player
    auto movement = sf::Vector2f {hero->getPosX(), hero->getPosY()};

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

    // the actual movement
    movement.x = movement.x * speed * sprite.getWidth() * static_cast<float>(deltaTime) / 1000000;
    movement.y = movement.y * speed * sprite.getHeight() * static_cast<float>(deltaTime) / 1000000;

    return movement;
}

void AggressiveMeleeEnemy::attack(FloorMap *floor, bool clicked) {
    // attack with the melee weapon, range is managed with the melee weapon range
    weapon->useWeapon(floor, this);
}

