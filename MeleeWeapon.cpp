//
// Created by apisti01 on 07/07/22.
//

#include <list>
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(float damage, std::string name, ItemRarity rarity, int price) : Weapon(std::move(name), rarity,price), damage(damage) {}

void MeleeWeapon::useWeapon(sf::Vector2f playerPosition, float facingAngle, float strength, FloorMap *floor) {
    auto hit = strength * damage;
    // check if the player is in the hit area
    if (checkEnemy(floor->player.get()))
        floor->player->receiveDamage(hit);

    /*
    // check if the enemies are on the hit area
    for( auto enemy : floor->roomList[floor->currentRoomIndex].enemyList)
        if (checkEnemy(enemy))
            enemy.receiveDamage(hit);
    */

}

bool MeleeWeapon::checkEnemy(const GameCharacter *character) {
    return false;
}

