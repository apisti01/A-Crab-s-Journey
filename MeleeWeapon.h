//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_MELEEWEAPON_H
#define MAIN_CPP_MELEEWEAPON_H

#include "Weapon.h"
#include "FloorMap.h"

enum class MeleeWeaponType {
    NaturalWeapon
};

class MeleeWeapon : public Weapon {
public:
    // Constructor and Destructor
    explicit MeleeWeapon(MeleeWeaponType type, std::string name = " ", float damage = 5, float range = 5,
                         ItemRarity rarity = ItemRarity::Common, int price = 50);
    ~MeleeWeapon() override = default;

    //  attack all the character that are in the hit area
    void useWeapon(FloorMap *floor, GameCharacter *attacker) override;

    // check if a particular victim is in range
    bool checkEnemy(const GameCharacter *victim, const GameCharacter *attacker) const;
private:
    // Damage dealt with the attack
    float damage;
    float range;
};


#endif //MAIN_CPP_MELEEWEAPON_H
