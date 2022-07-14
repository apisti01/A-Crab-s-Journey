//
// Created by apisti01 on 07/07/22.
//

#include <utility>

#include "Item.h"

Item::Item(std::string name, ItemRarity rarity, int price, int quantity, int slotOccupied) : name(std::move(name)),
           rarity(rarity), price(price), quantity(quantity), slotOccupied(slotOccupied) {
}
