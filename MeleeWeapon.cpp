//
// Created by apisti01 on 07/07/22.
//

#include <list>
#include <bitset>
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(MeleeWeaponType type, std::string name, float damage, float range, ItemRarity rarity, int price) :
        Weapon(std::move(name), rarity, price), damage(damage), range(range) {}

void MeleeWeapon::useWeapon(FloorMap *floor, GameCharacter *attacker) {
    auto hit = attacker->getStrength() * damage;
    // check if the player is in the hit area
    if (checkEnemy(floor->player.get(), attacker))
        floor->player->receiveDamage(hit);


    // check if the enemies are on the hit area
    for( auto & enemy : floor->roomList[floor->currentRoomIndex]->enemyList)
        if (checkEnemy(enemy.get(), attacker))
            enemy->receiveDamage(hit);
}

bool MeleeWeapon::checkEnemy(const GameCharacter *victim, const GameCharacter *attacker) const{
    // for every vertex of attacked
    for (int i = 0; i < 4; i++) {
        std::string x = std::bitset<2>(i).to_string();
        std::string y = std::bitset<2>((5 - i) % 4).to_string();

        sf::Vector2f pt(victim->collider.getPosX() + pow(-1, x[0]) * victim->collider.getWidth() / 2 *
                                                     cosf(victim->collider.getAngle()) + pow(-1, x[1]) * victim->collider.getHeight() / 2 * sinf(victim->collider.getAngle()),
                        victim->collider.getPosY() + pow(-1, y[0]) * victim->collider.getWidth() / 2 *
                                                     sinf(victim->collider.getAngle()) + pow(-1, y[1]) * victim->collider.getHeight() / 2 * cosf(victim->collider.getAngle()));

        float theta = atan2f(pt.y - attacker->getPosY(), pt.x - attacker->getPosX());
        float dist = sqrtf(powf(pt.x - attacker->getPosX(), 2) + powf(pt.y - attacker->getPosY(), 2));

        // minimum distance for the attacker to not attack itself
        auto attackerDistance = sqrt(powf(attacker->collider.getWidth(), 2) + powf(attacker->collider.getHeight(), 2));

        // check if the vertex is in the range of the weapon
        if (dist > attackerDistance && dist < range && theta > attacker->getAngle() - M_PI / 4 && theta < attacker->getAngle() + M_PI / 4)
            return true;
    }
    return false;
}

