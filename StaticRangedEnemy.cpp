//
// Created by apisti01 on 13/07/22.
//

#include "StaticRangedEnemy.h"
#include "Player.h"


StaticRangedEnemy::StaticRangedEnemy() : Enemy(" ", nullptr, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10) {}

void StaticRangedEnemy::dropItems() {
    // TODO random drop of items
}

sf::Vector2f StaticRangedEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime) {

    // the enemy is facing the player
    deltaAngle = atan2f(hero->getPosY() - this->getPosY(),hero->getPosX() - this->getPosX()) - getAngle();

    // a static enemy does not move
    return sf::Vector2f {0.f,0.f};
}

void StaticRangedEnemy::attack(FloorMap *floor, bool clicked) {
    // attack with the melee weapon
    weapon->useWeapon(floor, this);
}
