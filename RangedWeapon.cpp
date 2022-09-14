//
// Created by apisti01 on 07/07/22.
//

#include "RangedWeapon.h"
#include "FloorMap.h"

RangedWeapon::RangedWeapon(RangedWeaponType type, std::string name, float damage, float speed, sf::Vector2f dimensions,
                           bool isTracking, bool isShattering, ItemRarity rarity, int price)
                           : Weapon(std::move(name), rarity, price),
                           damage(damage), speed(speed), dimensions(dimensions), isTracking(isTracking), isShattering(isShattering) {
    switch (type) {
        case RangedWeaponType::NaturalWeapon:
        case RangedWeaponType::Rock:
            bulletTexture.loadFromFile("Assets/Object/Weapon/RangedWeapon/Natural/Bullet Texture.png"); // FIXME to complete
            break;
    }
}

void RangedWeapon::useWeapon(FloorMap *floor, GameCharacter *attacker) {
    // create new bullet with the weapon specifications
    // TODO: add the tangent component of player speed to the bullet speed
    Collider collider = {{attacker->getPosX() / Game::getInstance()->getWidth(),
                          attacker->getPosY() / Game::getInstance()->getHeight()},
                         dimensions, attacker->getAngle()};

    // insert the new bullet on the list
    floor->roomList[floor->currentRoomIndex]->bulletList.emplace_back(&collider, &bulletTexture, damage, speed, isTracking, isShattering, attacker);
}
