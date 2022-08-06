//
// Created by apisti01 on 04/08/22.
//

#include "DefensiveMeleeEnemy.h"
#include "../Player.h"

DefensiveMeleeEnemy::DefensiveMeleeEnemy(std::string name, const sf::Texture &texture, Collider collider,
                                         std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed,
                                         float maxSpeed, float armor, float maxArmor, float strength, float maxStrength,
                                         float XpReward, int coinsDropped, int pearlsDropped, float triggerRange) :
                                         Enemy(std::move(name), texture, std::move(collider), std::move(weapon), hp, maxHp,
                                               speed, maxSpeed, armor, maxArmor, strength, maxStrength, XpReward, coinsDropped,
                                               pearlsDropped), triggerRange(triggerRange) {
    origPosX = getPosX();
    origPosY = getPosY();
}

sf::Vector2f DefensiveMeleeEnemy::chase(const Player *hero, float &deltaAngle, int deltaTime, bool &triggered) {
    /* this function calculate the distance of the player form the original place of the enemy,
     * if the player is too close, the enemy chase him and attack him
     */

    // position of the player
    auto triggerDistance = sf::Vector2f {hero->getPosX(), hero->getPosY()};

    // coordinates relative to the original position of the enemy
    triggerDistance.x -= origPosX;
    triggerDistance.y -= origPosY;

    // distance from the original point
    auto distance = sqrtf(powf(triggerDistance.x, 2) + powf(triggerDistance.y, 2));

    // movement the enemy will do
    sf::Vector2f movement;

    if (distance < triggerRange){
        // position of the player
        movement = sf::Vector2f {hero->getPosX(), hero->getPosY()};
        triggered = true;
    }else{
        // original position
        movement = sf::Vector2f {origPosX, origPosY};
        triggered = false;
    }

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
    }else
        deltaAngle -= getAngle(); // face upward again

    // the actual movement
    movement.x = movement.x * speed * sprite.getWidth() * static_cast<float>(deltaTime) / 1000000;
    movement.y = movement.y * speed * sprite.getHeight() * static_cast<float>(deltaTime) / 1000000;

    return movement;
}

void DefensiveMeleeEnemy::attack(FloorMap *floor, bool clicked) {
    if (clicked)
    weapon->useWeapon(floor, this);
}

void DefensiveMeleeEnemy::dropItems() {
    // TODO

}

