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
#include "Collider.h"

class MeleeWeapon;

class FloorMap;

class GameCharacter {
public:
    // constructor and virtual destructor
    GameCharacter(std::string name, const sf::Texture &texture, Collider collider, std::unique_ptr<Weapon> weapon,
                  float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                  float maxStrength);
    virtual ~GameCharacter() = default;

    // getter and setter for character position
    void setPosition(float x, float y) {
        sprite.setPosition(sf::Vector2f(x, y));
        collider.setPosX(x);
        collider.setPosY(y);
    }
    float getPosX() const { return sprite.getPosition().x; }
    float getPosY() const { return sprite.getPosition().y; }

    // Getter and Setters for statistics
    const std::string &getName() const { return name;}
    void setName(std::string name) { GameCharacter::name = std::move(name);}

    float getHp() const { return hp; }
    void setHp(float hp) { GameCharacter::hp = hp; }

    float getMaxHp() const { return maxHp; }
    void setMaxHp(float maxHp) { GameCharacter::maxHp = maxHp; }

    float getSpeed() const { return speed; }
    void setSpeed(float speed) { GameCharacter::speed = speed; }

    float getMaxSpeed() const { return maxSpeed; }
    void setMaxSpeed(float maxSpeed) { GameCharacter::maxSpeed = maxSpeed; }

    float getArmor() const { return armor; }
    void setArmor(float armor) { GameCharacter::armor = armor; }

    float getMaxArmor() const { return maxArmor; }
    void setMaxArmor(float maxArmor) { GameCharacter::maxArmor = maxArmor; }

    float getStrength() const { return strength; }
    void setStrength(float strength) { GameCharacter::strength = strength; }

    float getMaxStrength() const { return maxStrength; }
    void setMaxStrength(float maxStrength) { GameCharacter::maxStrength = maxStrength; }

    // getter of weapon address
    Weapon* getWeapon(){ return weapon.get(); }

    // given a value for damage, receive damage
    void receiveDamage(float damage);

    // update game character
    virtual void update(int deltaTime, FloorMap *floor) = 0;

    // if weapon is ranged create bullet, if melee find the first in range enemy and gives it damages
    virtual void attack(FloorMap *floor, float bulletAngle) = 0;

    void draw(sf::RenderWindow &window);

    // getter of the coins
    int getCoins() const { return coins; }
    // given a value increases the coins
    void receiveCoins(int value) { coins += value; }

    Collider collider;

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

    // SFML Texture and Animated sprite
    sf::Texture texture;
    AnimatedSprite sprite;
    int fps = 10;

    // check if the new position is valid
    bool isValidPosition(FloorMap *floor);

    // update sprite and collider position and rotation values
    sf::Vector2f updateSpriteAndCollider(sf::Vector2f deltaPos, float deltaAngle, FloorMap *floor);

    // select movement animation based on movement direction and facing angle
    void selectAnimation(sf::Vector2f deltaPos);

    // the row of the Sprite sheet, that determine the behaviour of the animation
    int animationBehaviour = 0;

    // coin owned
    int coins;
};


#endif //MAIN_CPP_GAMECHARACTER_H
