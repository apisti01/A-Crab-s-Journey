//
// Created by apisti01 on 07/07/22.
//

#include "Wearable.h"

Wearable::Wearable(std::string name, WearablePieces type, float hp, float speed, float armor, float strength,
                   ItemRarity rarity, int price, int quantity, int slotOccupied)
                   : Item(std::move(name), rarity, price, quantity, slotOccupied),
                   type(type), hp(hp), speed(speed), armor(armor), strength(strength) {

}

