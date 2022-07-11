//
// Created by apisti01 on 10/07/22.
//

#include "Player.h"


void Player::attack(std::list<Enemy> enemyList) {

    // if ranged it delegates the creation of bullets, return the damage if melee
    auto damage = useWeapon();

    if (typeid(weapon.get()) == typeid(MeleeWeapon*)) {
        // find the first available enemy
        for (auto & enemy : enemyList) {
            if (checkEnemy(enemy)){
                enemy.receiveDamage(damage);
                break;
            }
        }
    }

}

std::unique_ptr<Wearable> Player::wearItem(std::unique_ptr<Wearable> item) {
    std::unique_ptr<Wearable> tmp = nullptr;
    switch (item->getType()) {
        case WearablePieces::Hat:
            tmp = std::move(hat);
            hat = std::move(item);
            return tmp;
        case WearablePieces::Shield:
            tmp = std::move(shield);
            shield = std::move(item);
            return tmp;
        case WearablePieces::Shell:
            tmp = std::move(shell);
            shell = std::move(item);
            return tmp;
    }

}

std::unique_ptr<Weapon> Player::changeWeapon(std::unique_ptr<Weapon> weapon1) {
    auto tmp = std::move(weapon);
    weapon = std::move(weapon1);
    return tmp;
}

Player::Player(std::string name, float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor,
               float strength, float maxStrength, std::unique_ptr<Weapon> weapon, std::string namePlayer,
               CrabSpecie crabSpecie, int coins) :
               GameCharacter(std::move(name),hp,maxHp,speed,maxSpeed,armor,maxArmor,strength,maxStrength,std::move(weapon)),
               namePlayer(std::move(namePlayer)),crabSpecie(crabSpecie),coins(coins) {}