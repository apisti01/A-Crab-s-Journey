//
// Created by apisti01 on 09/07/22.
//

#include <cmath>

#include "Bullet.h"
#include "FloorMap.h"

Bullet::Bullet(Collider* collider, sf::Texture* texture, float damage, float speed, bool isTracking, bool isShattering, GameCharacter* shooter)
        : collider(*collider), texture(*texture), damage(damage), speed(speed), isShattering(isShattering), isTracking(isTracking), shooter(shooter) {
    // get information from the collider
    pos = {collider->getPosX(), collider->getPosY()};
    dimensions = {collider->getWidth(), collider->getHeight()};
    direction = collider->getAngle();

    spriteScale = collider->getWidth() / texture->getSize().x;
}

void Bullet::draw(sf::RenderWindow &window) {
    sprite = {texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y)};
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(pos);
    sprite.setScale(spriteScale, spriteScale);

    window.draw(sprite);
    collider.draw(window);
}

void Bullet::update(int deltaTime) {
    // move the bullet
    collider.move(cosf(direction) * speed * Game::getInstance()->getUnit() * float(deltaTime) / pow(10, 6),
                  sinf(direction) * speed * Game::getInstance()->getUnit() * float(deltaTime) / pow(10, 6));
    pos = collider.getPosition();
}

bool Bullet::checkCollisions(FloorMap *floor) {
    // check collision with enemies
    for (auto &enemy : floor->roomList[floor->currentRoomIndex]->enemyList) {
        // TODO: check the individuals, not the names
        if (enemy->getName() != shooter->getName()) {
            if (collider.isCollidingWith(enemy->collider)) {
                enemy->receiveDamage(damage);
                return true;
            }
        }
    }

    // check collision with player
    // TODO: check the individuals, not the names
    if (floor->player->getName() != shooter->getName()) {
        if (collider.isCollidingWith(floor->player->collider)) {
            floor->player->receiveDamage(damage);
            return true;
        }
    }

    // check collision with obstacles
    for (auto &obstacle : floor->roomList[floor->currentRoomIndex]->obstacleList) {
        if (collider.isCollidingWith(obstacle.collider))
            return true;
    }

    // check collision with walls
    for (auto &wall : floor->roomList[floor->currentRoomIndex]->walls) {
        if (collider.isCollidingWith(wall))
            return true;
    }

    return false;
}
