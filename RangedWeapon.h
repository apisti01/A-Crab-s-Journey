//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_RANGEDWEAPON_H
#define MAIN_CPP_RANGEDWEAPON_H

#include <list>

#include "Weapon.h"

class RangedWeapon : public Weapon{
public:
    // Constructor and Destructor
    explicit RangedWeapon(float range, std::string name = " ", ItemRarity rarity = ItemRarity::Common, int price = 50);
    ~RangedWeapon() override = default;

    //TODO override useWeapon

private:
    // TODO function that manage bullets

    // Range of the weapon
    float range;

    // List of the bullets shot
    std::list<Bullet> bulletList {};

};


#endif //MAIN_CPP_RANGEDWEAPON_H
