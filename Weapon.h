//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_WEAPON_H
#define MAIN_CPP_WEAPON_H

#include "Item.h"

class Weapon : public Item{
public:
    // Constructor and Destructor
    explicit Weapon(std::string name, ItemRarity rarity, int price);
    ~Weapon() override = default;

    virtual float useWeapon() = 0;

protected:

};


#endif //MAIN_CPP_WEAPON_H
