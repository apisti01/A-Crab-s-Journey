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
#include "AnimatedSprite.h"


class GameCharacter {
public:
    // constructor and virtual destructor
    GameCharacter(std::string name, float hp, float maxHp, float speed, float maxSpeed, float armor,
                  float maxArmor, float strength, float maxStrength, std::unique_ptr<Weapon> weapon);
    virtual ~GameCharacter() = default;

    // TODO add move() and changeAngle()

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

    //SFML Texture of the sprite
    sf::Texture texture;

    //SFML Animated Sprite body
    AnimatedSprite sprite;
private:


};


#endif //MAIN_CPP_GAMECHARACTER_H
