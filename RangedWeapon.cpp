//
// Created by apisti01 on 07/07/22.
//

#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(float range, std::string name, ItemRarity rarity, int price) : Weapon(std::move(name), rarity, price), range(range) {

}
