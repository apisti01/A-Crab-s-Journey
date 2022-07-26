//
// Created by apisti01 on 09/07/22.
//

#include <cmath>

#include "Bullet.h"

Bullet::Bullet(float damage, float speed, float range, sf::Texture *texture, sf::Vector2f playerPosition,
               float direction, bool isTracking, bool isShattering)
                : damage(damage), speed(speed), range(range), direction(direction), isShattering(isShattering), isTracking(isTracking),
                  sprite(*texture) {
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(playerPosition);
    this->sprite.setScale(0.02, 0.02);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Bullet::move(int deltaTime) {
    sprite.move( cosf(direction)* speed * float (deltaTime)/1000000 * 50, sinf(direction) * speed * float (deltaTime)/1000000 * 50);
}
