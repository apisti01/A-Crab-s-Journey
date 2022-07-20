//
// Created by apisti01 on 07/07/22.
//

#include <list>
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(float damage, std::string name, ItemRarity rarity, int price) : Weapon(std::move(name), rarity,price), damage(damage) {}

void MeleeWeapon::useWeapon(sf::Vector2f playerPosition, sf::Vector2f bulletDirections, std::list<std::unique_ptr<Enemy>> &enemyList, float strength) {
    // find the first available enemy
    for (auto & enemy : enemyList) {
        if (checkEnemy(enemy.get())) {
            // the first one found gets damaged
            enemy->receiveDamage(damage * strength);
            break;
        }
    }
}

bool MeleeWeapon::checkEnemy(const Enemy *enemy) {
    return false;
}

