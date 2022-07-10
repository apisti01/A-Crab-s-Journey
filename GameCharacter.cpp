//
// Created by apisti01 on 29/06/22.
//


#include "GameCharacter.h"

class Enemy;

float GameCharacter::useWeapon() {
    return weapon->useWeapon() * strength;
}


void GameCharacter::receiveDamage(float damage) {
    hp -= damage;
}
