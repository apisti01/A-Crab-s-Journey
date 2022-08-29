//
// Created by apisti01 on 07/07/22.
//

#include "RangedWeapon.h"
#include "FloorMap.h"

RangedWeapon::RangedWeapon(RangedWeaponType type, std::string name, float damage, float speed, float range,
                           bool isTracking, bool isShattering, ItemRarity rarity, int price)
                           : Weapon(std::move(name), rarity, price),
                           range(range), damage(damage), speed(speed), isTracking(isTracking), isShattering(isShattering) {
    switch (type) {
        case RangedWeaponType::NaturalWeapon:
        case RangedWeaponType::Rock:
            bulletTexture.loadFromFile("others/bullet_rock.png"); // FIXME to complete
            break;
    }
}

void RangedWeapon::useWeapon(FloorMap *floor, GameCharacter *attacker) {
    // create new bullet with the weapon specifications
    // TODO: add the tangent component of player speed to the bullet speed
    Bullet tmp(damage, speed, range, &bulletTexture, sf::Vector2f {attacker->getPosX(),attacker->getPosY()}, attacker->getAngle(), isTracking, isShattering, attacker);

    // insert the new bullet on the list
    floor->roomList[floor->currentRoomIndex]->bulletList.push_back(tmp);
}
