//
// Created by apisti01 on 13/07/22.
//

#include "StaticRangedEnemy.h"
#include "../Player.h"

StaticRangedEnemy::StaticRangedEnemy(std::string name, const sf::Texture &texture, Collider collider,
                                     std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed, float maxSpeed,
                                     float armor, float maxArmor, float strength, float maxStrength, float XpReward,
                                     int coinsDropped, int pearlsDropped, int attackTimer) :
        Enemy(std::move(name), texture, std::move(collider), std::move(weapon), hp, maxHp, speed, maxSpeed, armor,
              maxArmor, strength, maxStrength, XpReward, coinsDropped, pearlsDropped, attackTimer) {
}

sf::Vector2f StaticRangedEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) {
    // the enemy is facing the player
    deltaAngle = atan2f(hero->getPosY() - this->getPosY(), hero->getPosX() - this->getPosX()) - getAngle();

    // always attack the player
    triggered = true;

    // a static enemy does not move
    return sf::Vector2f { 0.f, 0.f };
}

void StaticRangedEnemy::attack(FloorMap *floor, bool clicked) {
    // attack with the melee weapon
    weapon->useWeapon(floor, this);
}

void StaticRangedEnemy::dropItems() {
    // TODO random drop of items
}
