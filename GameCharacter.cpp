//
// Created by apisti01 on 29/06/22.
//


#include "GameCharacter.h"

#include <utility>

class Enemy;


void GameCharacter::receiveDamage(float damage) {
    hp -= damage;
}

GameCharacter::GameCharacter(const sf::Texture& texture, std::string name, float hp, float maxHp, float speed, float maxSpeed,
                             float armor, float maxArmor, float strength, float maxStrength,
                             std::unique_ptr<Weapon> weapon)
        : sprite(texture,sf::Vector2u(6,2)), texture(texture) ,name(std::move(name)), hp(hp), maxHp(maxHp), speed(speed), maxSpeed(maxSpeed), armor(armor), maxArmor(maxArmor),
          strength(strength), maxStrength(maxStrength), weapon(std::move(weapon)) {
}



void GameCharacter::draw(sf::RenderWindow &window) {
    sprite.draw(window);

    if (weapon){// in case there are bullets to be drawn
        weapon->draw(window);
    }
}

void GameCharacter::setPosition(float x, float y) {
    sprite.setPosition(sf::Vector2f(x,y));
}


