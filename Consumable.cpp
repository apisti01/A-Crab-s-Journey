//
// Created by apisti01 on 07/07/22.
//

#include "Consumable.h"

Consumable::Consumable(std::string name, float time, float hp, float speed, float armor, float strength,
                       ItemRarity rarity, int price, int quantity, int slotOccupied)
                       : Item(std::move(name), rarity, price, quantity, slotOccupied),
                       time(time), hp(hp), speed(speed), armor(armor), strength(strength){

}
