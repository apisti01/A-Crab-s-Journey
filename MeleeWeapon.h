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
    explicit MeleeWeapon(float damage, float range, std::string name = " ", ItemRarity rarity = ItemRarity::Common, int price = 50);
    ~MeleeWeapon() override = default;

    //  attack all the character that are in the hit area
    void useWeapon(sf::Vector2f playerPosition, float facingAngle, float strength, FloorMap *floor,
                   Collider &attackerCollider) override;

    // check if a particular character is in range
    bool checkEnemy(const GameCharacter *character, sf::Vector2f position, float angle, const Collider &attackerCollider);

private:
    // Damage dealt with the attack
    float damage;
    float range;
};


#endif //MAIN_CPP_MELEEWEAPON_H
