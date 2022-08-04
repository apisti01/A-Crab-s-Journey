//
// Created by apisti01 on 04/08/22.
//

#include "ChasingRangedEnemy.h"
#include "Player.h"

sf::Vector2f ChasingRangedEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) {
    // position of the player
    auto movement = sf::Vector2f {hero->getPosX(), hero->getPosY()};

    // coordinates relative to the position of the enemy
    movement.x -= getPosX();
    movement.y -= getPosY();

    // normalization
    float distance = sqrtf(powf(movement.x, 2) + powf(movement.y, 2));
    if (distance < triggerRange) {

        // variation in radians of the facing angle
        deltaAngle = atan2f(movement.y, movement.x) - getAngle();

        // normalization
        if (distance != 0) {
            movement.x = movement.x / distance;
            movement.y = movement.y / distance;
        }

        // triggered and will shoot
        triggered = true;

        // the actual movement
        movement.x = movement.x * speed * sprite.getWidth() * static_cast<float>(deltaTime) / 1000000;
        movement.y = movement.y * speed * sprite.getHeight() * static_cast<float>(deltaTime) / 1000000;
    } else {
        // stand still and does not attack
        movement = sf::Vector2f{0.f, 0.f};
        triggered = false;
    }

    return movement;
}

void ChasingRangedEnemy::attack(FloorMap *floor, bool triggered) {
    // when the player is close attacks with ranged weapon
    if (triggered)
        weapon->useWeapon(floor, this);
}

void ChasingRangedEnemy::dropItems() {
    // TODO
}
