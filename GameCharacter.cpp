//
// Created by apisti01 on 29/06/22.
//

#include <utility>

#include "GameCharacter.h"
#include "FloorMap.h"
#include "Weapon.h"

GameCharacter::GameCharacter(std::string name, const sf::Texture &texture, Collider collider,
                             std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed, float maxSpeed,
                             float armor, float maxArmor, float strength, float maxStrength,
                             sf::Vector2u imageCount, float units)
        : name(std::move(name)), sprite(texture, imageCount, units), collider(std::move(collider)),
          weapon(std::move(weapon)), hp(hp), maxHp(maxHp), speed(speed), maxSpeed(maxSpeed), armor(armor),
          maxArmor(maxArmor), strength(strength), maxStrength(maxStrength) {
}

void GameCharacter::receiveDamage(float damage) {
    hp -= damage * (10 - armor);

    // if health points are negative
    if (hp <= 0) {
        // TODO when killed the enemy update the observer in order to show the new enemy in the bestiary
    }
}

void GameCharacter::updateColliderAndSprite(sf::Vector2f deltaPos, float deltaAngle, FloorMap *floor) {
    collider.setPrevPosition(collider.getPosition());

    // update the collider with the just calculated values
    collider.move(deltaPos.x, deltaPos.y);
    collider.setAngle(collider.getAngle() + deltaAngle);

    // put it in a position in which does not overlap with other colliders
    checkCollisions(floor);

    // update the sprite
    sprite.setPosition(collider.getPosition());
    sprite.setAngle(collider.getAngle());
}

void GameCharacter::checkCollisions(FloorMap *floor) {
    // suppose the collider is not overlapping with any other
    collider.isColliding = false;

    // check collision with player
    if (!collider.isEqual(floor->player->collider))
        collider.isCollidingWith(floor->player->collider);

    // check collision with enemies
    for (auto &enemy : floor->roomList[floor->currentRoomIndex]->enemyList) {
        if (!collider.isEqual(enemy->collider))
            collider.isCollidingWith(enemy->collider);
    }

    // check collision with obstacles
    for (int i = 0; i < size(floor->roomList[floor->currentRoomIndex]->obstacleList); i++)
        collider.isCollidingWith(floor->roomList[floor->currentRoomIndex]->obstacleList[i].collider);

    // check collision with walls
    for (int i = 0; i < size(floor->roomList[floor->currentRoomIndex]->walls); i++)
        collider.isCollidingWith(floor->roomList[floor->currentRoomIndex]->walls[i]);
 }

void GameCharacter::selectAnimation() {
    // calculate deltaPos based on current and previous position
    sf::Vector2f deltaPos { collider.getPosX() - collider.getPrevPosX(), collider.getPosY() - collider.getPrevPosY() };

    // suppose the player is standing still
    animationBehaviour = 0;
    // if player is moving
    if (deltaPos.x != 0 || deltaPos.y != 0) {
        // calculate the two angles
        float velocityAngle = atan2f(deltaPos.y, deltaPos.x);
        float facingAngle = sprite.getAngle();
        float diff = fabsf(velocityAngle - facingAngle);

        // determine the animation based on the angle difference
        if (sinf(diff) > sqrtf(2) / 2 || sinf(diff) < -sqrtf(2) / 2) {
            // horizontal movement
            animationBehaviour = 1;
        } else {
            // vertical movement
            animationBehaviour = 2;
        }
    }
}

void GameCharacter::draw(sf::RenderWindow &window) {
    sprite.draw(window);
    collider.draw(window);
}
