//
// Created by apisti01 on 07/07/22.
//

#include <list>
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(float damage, std::string name, ItemRarity rarity, int price) : Weapon(std::move(name), rarity,price), damage(damage) {}

void
MeleeWeapon::useWeapon(sf::Vector2f playerPosition, float bulletAngle, std::list<std::unique_ptr<Enemy>> &enemyList,
                       float strength, FloorMap *floor) {
    // find the first available enemy
    for (auto & enemy : enemyList) {
        if (checkEnemy(enemy.get())) {
            // the first one found gets damaged
            enemy->receiveDamage(damage * strength); // FIXME
            break;
        }
    }
}

bool MeleeWeapon::checkEnemy(const Enemy *enemy) {
    return false;
}

