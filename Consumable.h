//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_CONSUMABLE_H
#define MAIN_CPP_CONSUMABLE_H

#include "Item.h"

class Consumable : public Item {
public:
    //Constructor and Destructor
    explicit Consumable(std::string name, float time = 60, float hp = 0, float speed = 0, float armor = 0, float strength = 0,
                        ItemRarity rarity = ItemRarity::Common, int price = 50, int quantity = 1, int slotOccupied = 1);
    ~Consumable() override = default;

    // Use the consumable  TODO specify the behavior
    int useItem();

    // eliminate the consumable from inventory
    int dropItem();

private:
    // Time that the consumable last
    float time;

    // Bonus added to the player statistics
    float hp;
    float speed;
    float armor;
    float strength;
};


#endif //MAIN_CPP_CONSUMABLE_H
