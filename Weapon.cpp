//
// Created by apisti01 on 07/07/22.
//

#include "Weapon.h"

#include <utility>

Weapon::Weapon(std::string name, ItemRarity rarity, int price) : Item(std::move(name), rarity, price) {

}
