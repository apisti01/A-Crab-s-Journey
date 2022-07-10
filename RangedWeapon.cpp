//
// Created by apisti01 on 07/07/22.
//

#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(sf::Sprite bulletBody, float damage, float speed, float range, bool isTracking,
                           bool isShattering,
                           ItemRarity rarity, std::string name, int price)
                           : Weapon(std::move(name), rarity, price), range(range),
                           body(std::move(bulletBody)), damage(damage), speed(speed), isTracking(isTracking), isShattering(isShattering){

}

float RangedWeapon::useWeapon() {
    Bullet tmp(damage,speed,range,body,isTracking,isShattering);
    bulletList.push_back(tmp);
}
