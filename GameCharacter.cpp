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
                             sf::Vector2u imageCount)
        : name(std::move(name)), sprite(texture, imageCount), collider(std::move(collider)),
          weapon(std::move(weapon)), hp(hp), maxHp(maxHp), speed(speed), maxSpeed(maxSpeed), armor(armor),
          maxArmor(maxArmor), strength(strength), maxStrength(maxStrength) {
}

void GameCharacter::receiveDamage(float damage) {
    hp -= damage * (1 -  armor);
}

void GameCharacter::draw(sf::RenderWindow &window) {
    sprite.draw(window);
    collider.draw(window);
}

sf::Vector2f GameCharacter::updateSpriteAndCollider(sf::Vector2f deltaPos, float deltaAngle, FloorMap *floor) {
    // update the sprite with the just calculated values
    sprite.move(deltaPos.x, deltaPos.y);
    collider.setPosX(sprite.getPosition().x);
    collider.setPosY(sprite.getPosition().y);
    sprite.setAngle(sprite.getAngle() + deltaAngle);
    collider.setAngle(sprite.getAngle());

    // check if the next position and rotation is valid
    if (!isValidPosition(floor)) {
        sprite.setPosition({ sprite.getPosition().x - deltaPos.x, sprite.getPosition().y - deltaPos.y });
        sprite.setAngle(sprite.getAngle() - deltaAngle);

        deltaPos = {0, 0};
    }

    // update the collider
    collider.setPosX(sprite.getPosition().x);
    collider.setPosY(sprite.getPosition().y);
    collider.setAngle(sprite.getAngle());

    return deltaPos;
}

bool GameCharacter::isValidPosition(FloorMap *floor) {
    // TODO: check collision with every other game character in the room by override

    // check collision with obstacles
    collider.isColliding = false;
    for (int i = 0; i < size(floor->roomList[floor->currentRoomIndex]->obstacleList); i++) {
        floor->roomList[floor->currentRoomIndex]->obstacleList[i].collider.isColliding = false;
        collider.isCollidingWith(floor->roomList[floor->currentRoomIndex]->obstacleList[i].collider);
    }

    // check collision with walls
    for (int i = 0; i < size(floor->roomList[floor->currentRoomIndex]->walls); i++) {
        floor->roomList[floor->currentRoomIndex]->walls[i].isColliding = false;
        collider.isCollidingWith(floor->roomList[floor->currentRoomIndex]->walls[i]);
    }

    return !collider.isColliding;
}

void GameCharacter::selectAnimation(sf::Vector2f deltaPos) {
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
