//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_MELEEWEAPON_H
#define MAIN_CPP_MELEEWEAPON_H

#include "Weapon.h"

class MeleeWeapon : public Weapon{
public:
    // Constructor and Destructor
    explicit MeleeWeapon(float damage, std::string name = " ", ItemRarity rarity = ItemRarity::Common, int price = 50);
    ~MeleeWeapon() override = default;

    // override useWeapon
    float useWeapon() override;

private:
    // Damage dealt with the attack
    float damage;
};


#endif //MAIN_CPP_MELEEWEAPON_H
