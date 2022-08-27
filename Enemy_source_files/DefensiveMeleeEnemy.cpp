//
// Created by apisti01 on 04/08/22.
//

#include "DefensiveMeleeEnemy.h"
#include "../Player.h"

DefensiveMeleeEnemy::DefensiveMeleeEnemy(std::string name, const sf::Texture &texture, Collider collider,
                                         std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed,
                                         float maxSpeed, float armor, float maxArmor, float strength, float maxStrength,
                                         float XpReward, int coinsDropped, int pearlsDropped, int attackTimer,
                                         float triggerRange) :
                                         Enemy(std::move(name), texture, std::move(collider), std::move(weapon), hp,
                                               maxHp, speed, maxSpeed, armor, maxArmor, strength, maxStrength, XpReward,
                                               coinsDropped, pearlsDropped, attackTimer), triggerRange(triggerRange) {
    origPosX = getPosX();
    origPosY = getPosY();
}

sf::Vector2f DefensiveMeleeEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) {
    // distance from the two character point
    float distance = sqrtf(powf(hero->getPosX() - getPosX(), 2) + powf(hero->getPosY() - getPosY(), 2));

    // movement the enemy will do
    sf::Vector2f deltaPos;

    // if the player is near enough
    if (distance <= triggerRange) {
        deltaPos = {hero->getPosX() - getPosX(), hero->getPosY() - getPosY()};
        triggered = true;
    } else {
        deltaPos = {origPosX - getPosX(), origPosY - getPosY()};
        triggered = false;
    }

    // variation in radians of the facing angle
    deltaAngle = atan2f(deltaPos.y, deltaPos.x) - getAngle();

    // normalization
    float norm = sqrtf(powf(deltaPos.x, 2) + powf(deltaPos.y, 2));
    if (norm != 0) {
        deltaPos.x = deltaPos.x / norm;
        deltaPos.y = deltaPos.y / norm;
    }

    // the actual movement
    deltaPos.x = deltaPos.x * speed * sprite.getWidth() * static_cast<float>(deltaTime) / pow(10, 6);
    deltaPos.y = deltaPos.y * speed * sprite.getHeight() * static_cast<float>(deltaTime) / pow(10, 6);

    return deltaPos;
}

void DefensiveMeleeEnemy::attack(FloorMap *floor, bool triggered) {
    if (triggered)
        weapon->useWeapon(floor, this);
}

void DefensiveMeleeEnemy::dropItems() {
    // TODO random drop of items
}

