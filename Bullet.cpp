//
// Created by apisti01 on 09/07/22.
//

#include <cmath>

#include "Bullet.h"
#include "FloorMap.h"

Bullet::Bullet(float damage, float speed, float range, sf::Texture* texture, sf::Vector2f playerPosition,
               float direction, bool isTracking, bool isShattering, GameCharacter* shooter)
        : damage(damage), speed(speed), range(range), direction(direction), isShattering(isShattering),
          isTracking(isTracking), sprite(*texture), shooter(shooter) {
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(playerPosition);
    this->sprite.setScale(0.02, 0.02);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Bullet::update(int deltaTime) {
    // move the bullet
    sprite.move(cosf(direction) * speed * float (deltaTime) / pow(10, 6) * 120, sinf(direction) * speed * float (deltaTime) / pow(10, 6) * 120);
}

bool Bullet::checkCollisions(FloorMap *floor) {
    // check collision with enemies
    for (auto &enemy : floor->roomList[floor->currentRoomIndex]->enemyList) {
        // TODO: check the individuals, not the names
        if (enemy->getName() != shooter->getName()) {
            float teta = enemy->getAngle() -
                         atan2f(sprite.getPosition().y - enemy->getPosY(), sprite.getPosition().x - enemy->getPosX());
            while (teta <= -M_PI || teta > M_PI)
                teta -= fabs(teta) / teta * 2 * M_PI;

            float dist = sqrtf(powf(sprite.getPosition().x - enemy->getPosX(), 2) +
                               powf(sprite.getPosition().y - enemy->getPosY(), 2));

            // check if the vertex is in the other collider
            if (dist * cosf(teta) > -enemy->collider.getWidth() / 2 &&
                dist * cosf(teta) < enemy->collider.getWidth() / 2 &&
                dist * sinf(teta) > -enemy->collider.getHeight() / 2 &&
                dist * sinf(teta) < enemy->collider.getHeight() / 2) {
                enemy->receiveDamage(damage);
                return true;
            }
        }
    }

    // check collision with player
    // TODO: check the individuals, not the names
    if (floor->player->getName() != shooter->getName()) {
        float teta = floor->player->getAngle() - atan2f(sprite.getPosition().y - floor->player->getPosY(),
                                                        sprite.getPosition().x - floor->player->getPosX());
        while (teta <= -M_PI || teta > M_PI)
            teta -= fabs(teta) / teta * 2 * M_PI;

        float dist = sqrtf(powf(sprite.getPosition().x - floor->player->getPosX(), 2) +
                           powf(sprite.getPosition().y - floor->player->getPosY(), 2));

        // check if the vertex is in the other collider
        if (dist * cosf(teta) > -floor->player->collider.getWidth() / 2 &&
            dist * cosf(teta) < floor->player->collider.getWidth() / 2 &&
            dist * sinf(teta) > -floor->player->collider.getHeight() / 2 &&
            dist * sinf(teta) < floor->player->collider.getHeight() / 2) {
            floor->player->receiveDamage(damage);
            return true;
        }
    }

    // check collision with obstacles
    for (auto &obstacle : floor->roomList[floor->currentRoomIndex]->obstacleList) {
        float teta = obstacle.collider.getAngle() - atan2f(sprite.getPosition().y - obstacle.getPosY(), sprite.getPosition().x - obstacle.getPosX());
        while (teta <= -M_PI || teta > M_PI)
            teta -= fabs(teta) / teta * 2 * M_PI;

        float dist = sqrtf(powf(sprite.getPosition().x - obstacle.getPosX(), 2) + powf(sprite.getPosition().y - obstacle.getPosY(), 2));

        // check if the vertex is in the other collider
        if (dist * cosf(teta) > -obstacle.collider.getWidth() / 2 && dist * cosf(teta) < obstacle.collider.getWidth() / 2 &&
            dist * sinf(teta) > -obstacle.collider.getHeight() / 2 && dist * sinf(teta) < obstacle.collider.getHeight() / 2) {
            return true;
        }
    }

    // check collision with walls
    for (auto &wall : floor->roomList[floor->currentRoomIndex]->walls) {
        float teta = wall.getAngle() - atan2f(sprite.getPosition().y - wall.getPosY(), sprite.getPosition().x - wall.getPosX());
        while (teta <= -M_PI || teta > M_PI)
            teta -= fabs(teta) / teta * 2 * M_PI;

        float dist = sqrtf(powf(sprite.getPosition().x - wall.getPosX(), 2) + powf(sprite.getPosition().y - wall.getPosY(), 2));

        // check if the vertex is in the other collider
        if (dist * cosf(teta) > -wall.getWidth() / 2 && dist * cosf(teta) < wall.getWidth() / 2 &&
            dist * sinf(teta) > -wall.getHeight() / 2 && dist * sinf(teta) < wall.getHeight() / 2) {
            return true;
        }
    }

    return false;
}

