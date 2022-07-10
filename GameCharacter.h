//
// Created by apisti01 on 29/06/22.
//

#ifndef MAIN_CPP_GAMECHARACTER_H
#define MAIN_CPP_GAMECHARACTER_H

#include <string>
#include <memory>
#include <list>

#include "Item.h"
#include "Weapon.h"
#include "MeleeWeapon.h"


class GameCharacter {
public:
    //TODO add constructor and virtual destructor

    virtual ~GameCharacter() = default;

    //TODO add move() and changeAngle()

    void receiveDamage(float damage);

    float useWeapon();

protected:
    //Character name
    std::string name;

    //Statistics
    float hp, maxHp;
    float speed, maxSpeed;
    float armor, maxArmor;
    float strength, maxStrength;

    // Weapon wielded
    std::unique_ptr<Weapon> weapon;

    //TODO add Animated Sprite body

private:


};


#endif //MAIN_CPP_GAMECHARACTER_H
