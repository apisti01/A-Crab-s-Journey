//
// Created by apisti01 on 09/07/22.
//

#include <cmath>

#include "Bullet.h"
#include "FloorMap.h"

Bullet::Bullet(float damage, float speed, float range, sf::Texture* texture, sf::Vector2f pos,
               float direction, bool isTracking, bool isShattering, GameCharacter* shooter)
        : damage(damage), speed(speed), range(range), pos(pos), direction(direction), isShattering(isShattering),
        isTracking(isTracking), shooter(shooter), texture(*texture) {
}

void Bullet::draw(sf::RenderWindow &window) {
    sprite = {texture, sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y)};
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setPosition(pos);
    sprite.setScale(0.03, 0.03);

    window.draw(sprite);
}

void Bullet::update(int deltaTime) {
    // move the bullet
    pos.x += cosf(direction) * speed * float(deltaTime) / pow(10, 6) * 120;
    pos.y += sinf(direction) * speed * float(deltaTime) / pow(10, 6) * 120;
}

bool Bullet::checkCollisions(FloorMap *floor) {
    // check collision with enemies
    for (auto &enemy : floor->roomList[floor->currentRoomIndex]->enemyList) {
        // TODO: check the individuals, not the names
        if (enemy->getName() != shooter->getName()) {
            float teta = enemy->getAngle() - atan2f(pos.y - enemy->getPosY(), pos.x - enemy->getPosX());
            while (teta <= -M_PI || teta > M_PI)
                teta -= fabs(teta) / teta * 2 * M_PI;

            float dist = sqrtf(powf(pos.x - enemy->getPosX(), 2) + powf(pos.y - enemy->getPosY(), 2));

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
        float teta = floor->player->getAngle() - atan2f(pos.y - floor->player->getPosY(), pos.x - floor->player->getPosX());
        while (teta <= -M_PI || teta > M_PI)
            teta -= fabs(teta) / teta * 2 * M_PI;

        float dist = sqrtf(powf(pos.x - floor->player->getPosX(), 2) + powf(pos.y - floor->player->getPosY(), 2));

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
        float teta = obstacle.collider.getAngle() - atan2f(pos.y - obstacle.getPosY(), pos.x - obstacle.getPosX());
        while (teta <= -M_PI || teta > M_PI)
            teta -= fabs(teta) / teta * 2 * M_PI;

        float dist = sqrtf(powf(pos.x - obstacle.getPosX(), 2) + powf(pos.y - obstacle.getPosY(), 2));

        // check if the vertex is in the other collider
        if (dist * cosf(teta) > -obstacle.collider.getWidth() / 2 && dist * cosf(teta) < obstacle.collider.getWidth() / 2 &&
            dist * sinf(teta) > -obstacle.collider.getHeight() / 2 && dist * sinf(teta) < obstacle.collider.getHeight() / 2) {
            return true;
        }
    }

    // check collision with walls
    for (auto &wall : floor->roomList[floor->currentRoomIndex]->walls) {
        float teta = wall.getAngle() - atan2f(pos.y - wall.getPosY(), pos.x - wall.getPosX());
        while (teta <= -M_PI || teta > M_PI)
            teta -= fabs(teta) / teta * 2 * M_PI;

        float dist = sqrtf(powf(pos.x - wall.getPosX(), 2) + powf(pos.y - wall.getPosY(), 2));

        // check if the vertex is in the other collider
        if (dist * cosf(teta) > -wall.getWidth() / 2 && dist * cosf(teta) < wall.getWidth() / 2 &&
            dist * sinf(teta) > -wall.getHeight() / 2 && dist * sinf(teta) < wall.getHeight() / 2) {
            return true;
        }
    }

    return false;
}

