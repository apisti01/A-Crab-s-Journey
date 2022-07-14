//
// Created by apisti01 on 29/06/22.
//

#ifndef MAIN_CPP_GAMECHARACTER_H
#define MAIN_CPP_GAMECHARACTER_H

#include <string>
#include <memory>
#include <list>
#include <cmath>

#include "Item.h"
#include "Weapon.h"
#include "MeleeWeapon.h"
#include "AnimatedSprite.h"


class GameCharacter {
public:
    // constructor and virtual destructor
    GameCharacter(const sf::Texture& texture, std::string name, float hp, float maxHp, float speed, float maxSpeed,
                  float armor, float maxArmor, float strength, float maxStrength, std::unique_ptr<Weapon> weapon);
    virtual ~GameCharacter() = default;


    void setPosition(float x, float y);

    // given a value for damage, receive damage
    void receiveDamage(float damage);

    void draw(sf::RenderWindow& window);

protected:
    // character name
    std::string name;

    // statistics
    float hp, maxHp;
    float speed, maxSpeed;
    float armor, maxArmor;
    float strength, maxStrength;

    // Weapon wielded
    std::unique_ptr<Weapon> weapon;

    // SFML Texture of the sprite
    sf::Texture texture;

    // SFML Animated Sprite body
    AnimatedSprite sprite;

    // the row of the Sprite sheet, that determine the behaviour of the animation
    int animationBehaviour = 0;

private:

};


#endif //MAIN_CPP_GAMECHARACTER_H
