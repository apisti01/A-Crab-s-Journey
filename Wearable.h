//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_WEARABLE_H
#define MAIN_CPP_WEARABLE_H

#include "Item.h"

enum class WearablePieces {
    Hat,
    Shield,
    Shell,
};

class Wearable : public Item{
public:
    // Constructor and destructor
    Wearable(std::string name, WearablePieces type, float hp = 0, float speed = 0, float armor = 0, float strength = 0,
             ItemRarity rarity = ItemRarity::Common, int price = 50, int quantity = 1, int slotOccupied = 1);
    ~Wearable() override = default;

    // Getters
    WearablePieces getType() const { return type; }
    float getHp() const { return hp; }
    float getSpeed() const { return speed; }
    float getArmor() const { return armor; }
    float getStrength() const { return strength; }

private:
    // piece's type
    WearablePieces type;

    // Bonus added to the player statistics
    float hp = 0;
    float speed = 0;
    float armor = 0;
    float strength = 0;
};


#endif //MAIN_CPP_WEARABLE_H
