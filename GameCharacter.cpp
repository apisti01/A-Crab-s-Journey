//
// Created by apisti01 on 29/06/22.
//


#include "GameCharacter.h"
#include <utility>

class Enemy;

float GameCharacter::useWeapon() {
    return weapon->useWeapon() * strength;
}

void GameCharacter::receiveDamage(float damage) {
    hp -= damage;
}

GameCharacter::GameCharacter(std::string name, float hp, float maxHp, float speed, float maxSpeed, float armor,
                             float maxArmor, float strength, float maxStrength, std::unique_ptr<Weapon> weapon)
        : name(std::move(name)), hp(hp), maxHp(maxHp), speed(speed), maxSpeed(maxSpeed), armor(armor), maxArmor(maxArmor),
          strength(strength), maxStrength(maxStrength), weapon(std::move(weapon)) {}
