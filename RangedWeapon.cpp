//
// Created by apisti01 on 07/07/22.
//

#include "RangedWeapon.h"
#include "FloorMap.h"


RangedWeapon::RangedWeapon(RangedWeaponType type, float damage, float speed, float range, bool isTracking,
                           bool isShattering, ItemRarity rarity, std::string name, int price)
                           : Weapon(std::move(name), rarity, price), range(range),
                           damage(damage), speed(speed), isTracking(isTracking), isShattering(isShattering) {
    switch (type) {
        case RangedWeaponType::Rock:
            bulletTexture.loadFromFile("others/bullet_rock.png"); // FIXME to complete
    }
}

void RangedWeapon::useWeapon(FloorMap *floor, GameCharacter *attacker) {

    // create new bullet with the weapon specifications
    Bullet tmp(damage, speed, range, &bulletTexture, sf::Vector2f {attacker->getPosX(),attacker->getPosY()}, attacker->getAngle(), isTracking, isShattering);

    // insert the new bullet on the list
    floor->roomList[floor->currentRoomIndex]->bulletList.push_back(tmp);
}
