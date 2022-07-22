//
// Created by apisti01 on 09/07/22.
//

#include <cmath>

#include "Bullet.h"

Bullet::Bullet(float damage, float speed, float range, const sf::Sprite &sprite, sf::Vector2f playerPosition,
               float direction, bool isTracking, bool isShattering)
                : damage(damage), speed(speed), range(range), sprite(sf::Sprite(sprite)), direction(direction), isShattering(isShattering), isTracking(isTracking) {
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(playerPosition);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Bullet::move(int deltaTime) {
    sprite.move( cosf(direction)* speed * float (deltaTime), sinf(direction) * speed * float (deltaTime));
}
