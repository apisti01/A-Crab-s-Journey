//
// Created by apisti01 on 29/06/22.
//


#include "GameCharacter.h"

#include <utility>

class Enemy;

GameCharacter::GameCharacter(std::string name, const sf::Texture &texture, Collider collider, std::unique_ptr<Weapon> weapon,
                             float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
                             float maxStrength)
        : name(std::move(name)), sprite(texture, sf::Vector2u(6, 3)), texture(texture), collider(collider),
        weapon(std::move(weapon)), hp(hp), maxHp(maxHp), speed(speed), maxSpeed(maxSpeed), armor(armor),
        maxArmor(maxArmor), strength(strength), maxStrength(maxStrength) {
}

void GameCharacter::receiveDamage(float damage) {
    hp -= damage * (1 -  armor);
}

void GameCharacter::draw(sf::RenderWindow &window) {
    sprite.draw(window);
    collider.draw(window);

    // if the weapon is ranged
    if (weapon) {
        // draw its bullets
        weapon->draw(window);
    }
}
