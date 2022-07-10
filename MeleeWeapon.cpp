//
// Created by apisti01 on 07/07/22.
//

#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(float damage, std::string name, ItemRarity rarity, int price) : Weapon(std::move(name), rarity,price), damage(damage){

}

float MeleeWeapon::useWeapon() {
    return damage;
}
