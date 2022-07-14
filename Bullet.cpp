//
// Created by apisti01 on 09/07/22.
//

#include "Bullet.h"

Bullet::Bullet(float damage, float speed, float range, const sf::Sprite &sprite, sf::Vector2f playerPosition,
               sf::Vector2f directions, bool isTracking, bool isShattering)
                : damage(damage), speed(speed), range(range), sprite(sf::Sprite(sprite)), directions(directions), isShattering(isShattering), isTracking(isTracking) {
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(playerPosition);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Bullet::move(int deltaTime) {
    sprite.move(directions.x * speed * float (deltaTime), directions.y * speed * float (deltaTime));
}
