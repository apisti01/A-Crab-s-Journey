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
#include "AnimatedSprite.h"
#include "Weapon.h"

class MeleeWeapon;


class GameCharacter {
public:
    // constructor and virtual destructor
    GameCharacter(const sf::Texture& texture, std::string name, float hp, float maxHp, float speed, float maxSpeed,
                  float armor, float maxArmor, float strength, float maxStrength, std::unique_ptr<Weapon> weapon);
    virtual ~GameCharacter() = default;

    // getter and setter for character position
    void setPosition(float x, float y) {
        sprite.setPosition(sf::Vector2f(x,y));
    }
    float getPosX() const {
        return sprite.getPosition().x;
    }
    float getPosY() const {
        return sprite.getPosition().y;
    }

    // Getter and Setters for statistics
    const std::string &getName() const { return name;}
    void setName(std::string name) { GameCharacter::name = std::move(name);}

    float getHp() const { return hp;}
    void setHp(float hp) { GameCharacter::hp = hp;}

    float getMaxHp() const { return maxHp;}
    void setMaxHp(float maxHp) { GameCharacter::maxHp = maxHp;}

    float getSpeed() const { return speed;}
    void setSpeed(float speed) { GameCharacter::speed = speed;}

    float getMaxSpeed() const { return maxSpeed;}
    void setMaxSpeed(float maxSpeed) { GameCharacter::maxSpeed = maxSpeed; }

    float getArmor() const { return armor;}
    void setArmor(float armor) { GameCharacter::armor = armor;}

    float getMaxArmor() const { return maxArmor;}
    void setMaxArmor(float maxArmor) { GameCharacter::maxArmor = maxArmor;}

    float getStrength() const { return strength;}
    void setStrength(float strength) { GameCharacter::strength = strength;}

    float getMaxStrength() const { return maxStrength;}
    void setMaxStrength(float maxStrength) { GameCharacter::maxStrength = maxStrength;}

    // getter of weapon address
    Weapon* getWeapon(){ return weapon.get();}

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
