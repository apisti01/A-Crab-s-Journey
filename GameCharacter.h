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
#include "Collider.h"
#include "Weapon.h"

class MeleeWeapon;
class FloorMap;

class GameCharacter {
public:
    // constructor and virtual destructor
    GameCharacter(std::string name, const sf::Texture &texture, Collider collider, std::unique_ptr<Weapon> weapon,
                  float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                  float maxStrength, sf::Vector2u imageCount, float units);
    virtual ~GameCharacter() = default;

    // getter and setter for character position
    virtual void setPosition(sf::Vector2f pos) {
        collider.setPosition(pos);
        sprite.setPosition(pos);
    }
    sf::Vector2f getPosition() const { return collider.getPosition(); }
    float getPosX() const { return collider.getPosX(); }
    void setPosX(float posX) {
        collider.setPosX(posX);
        sprite.setPosition({posX, sprite.getPosition().y});
    }
    float getPosY() const { return collider.getPosY(); }
    void setPosY(float posY) {
        collider.setPosY(posY);
        sprite.setPosition({sprite.getPosition().x, posY});
    }

    float getAngle() const { return collider.getAngle(); }

    // Getter and Setters for statistics
    const std::string &getName() const { return name; }
    void setName(std::string name) { GameCharacter::name = std::move(name); }

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
    Weapon* getWeapon() { return weapon.get(); }

    // given a value for damage, receive damage
    void receiveDamage(float damage);

    // update game character
    virtual void update(int deltaTime, FloorMap *floor, bool clicked, sf::RenderWindow &window) = 0;

    // if weapon is ranged create bullet, if melee find the first in range enemy and gives it damages
    virtual void attack(FloorMap *floor, bool clicked) = 0;

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
    AnimatedSprite sprite;
    int fps = 10;

    // update collider and sprite position and rotation values
    void updateColliderAndSprite(sf::Vector2f deltaPos, float deltaAngle, FloorMap *floor);

    // check if the new position is valid
    void checkCollisions(FloorMap *floor);

    // select movement animation based on movement direction and facing angle
    void selectAnimation();

    // the row of the Sprite sheet, that determine the behaviour of the animation
    int animationBehaviour = 0;

    // coin owned
    int coins = 0;
};


#endif //MAIN_CPP_GAMECHARACTER_H
