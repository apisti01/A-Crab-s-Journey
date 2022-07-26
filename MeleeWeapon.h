//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_MELEEWEAPON_H
#define MAIN_CPP_MELEEWEAPON_H

#include "Weapon.h"
#include "Enemy.h"
#include "FloorMap.h"


class MeleeWeapon : public Weapon{
public:
    // Constructor and Destructor
    explicit MeleeWeapon(float damage, std::string name = " ", ItemRarity rarity = ItemRarity::Common, int price = 50);
    ~MeleeWeapon() override = default;

    // attack the nearest available enemy
    void useWeapon(sf::Vector2f playerPosition, float facingAngle, float strength, FloorMap *floor) override;

    // TODO: write definition for the selection of hit enemy
    bool checkEnemy(const GameCharacter *character);

private:
    // Damage dealt with the attack
    float damage;
};


#endif //MAIN_CPP_MELEEWEAPON_H
