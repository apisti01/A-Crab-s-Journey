//
// Created by apisti01 on 07/07/22.
//

#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(sf::Sprite bulletBody, float damage, float speed, float range, bool isTracking,
                           bool isShattering, ItemRarity rarity, std::string name, int price)
                           : Weapon(std::move(name), rarity, price), range(range), sprite(std::move(bulletBody)),
                           damage(damage), speed(speed), isTracking(isTracking), isShattering(isShattering) {
}

void RangedWeapon::useWeapon(sf::Vector2f playerPosition, float bulletAngle,
                             std::list<std::unique_ptr<Enemy>> &enemyList, float strength) {
    // create new bullet with the weapon specifications
    Bullet tmp(damage, speed, range, sprite, playerPosition, bulletAngle, isTracking, isShattering);

    // insert the new bullet on the list
    bulletList.push_back(tmp);
}

void RangedWeapon::draw(sf::RenderWindow &window) {
    // draw the bullets on their positions
    for (auto bullet : bulletList) {
        bullet.draw(window);
    }
}

void RangedWeapon::update(int deltaTime) {
    // move the bullets on their trajectory
    for (auto bullet : bulletList) {
        bullet.move(deltaTime);
    }
}
