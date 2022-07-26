//
// Created by apisti01 on 07/07/22.
//

#include "RangedWeapon.h"
#include "FloorMap.h"


RangedWeapon::RangedWeapon(const sf::Texture& bulletBody, float damage, float speed, float range, bool isTracking,
                           bool isShattering, ItemRarity rarity, std::string name, int price)
                           : Weapon(std::move(name), rarity, price), range(range), bulletTexture(bulletBody),
                           damage(damage), speed(speed), isTracking(isTracking), isShattering(isShattering) {
    sprite.setScale(0.02, 0.02);

}

void
RangedWeapon::useWeapon(sf::Vector2f playerPosition, float bulletAngle, std::list<std::unique_ptr<Enemy>> &enemyList,
                        float strength, FloorMap *floor) {

    // create new bullet with the weapon specifications
    Bullet tmp(damage, speed, range, sprite, playerPosition, bulletAngle, isTracking, isShattering);

    // insert the new bullet on the list
    floor->roomList[floor->currentRoomIndex].bulletList.push_back(tmp);
}
