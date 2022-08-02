//
// Created by apisti01 on 07/07/22.
//

#include <list>
#include <bitset>
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(float damage, float range, std::string name, ItemRarity rarity, int price) : Weapon(std::move(name), rarity,price), damage(damage), range(range) {}

void MeleeWeapon::useWeapon(sf::Vector2f playerPosition, float facingAngle, float strength, FloorMap *floor,
                            Collider &attackerCollider) {
    auto hit = strength * damage;
    // check if the player is in the hit area
    if (checkEnemy(floor->player.get(), playerPosition, facingAngle, attackerCollider))
        floor->player->receiveDamage(hit);

    /*
    // check if the enemies are on the hit area
    for( auto enemy : floor->roomList[floor->currentRoomIndex].enemyList)
        if (checkEnemy(enemy))
            enemy.receiveDamage(hit);
    */ // TODO uncomment and correct once enemies work

}

bool MeleeWeapon::checkEnemy(const GameCharacter *character, sf::Vector2f position, float angle,
                             const Collider &attackerCollider) {

    // for every vertex of attacked
    for (int i = 0; i < 4; i++) {
        std::string x = std::bitset<2>(i).to_string();
        std::string y = std::bitset<2>((5 - i) % 4).to_string();

        sf::Vector2f pt(character->collider.getPosX() + pow(-1, x[0]) * character->collider.getWidth() / 2 *
                        cosf(character->collider.getAngle()) + pow(-1, x[1]) * character->collider.getHeight() / 2 * sinf(character->collider.getAngle()),
                        character->collider.getPosY() + pow(-1, y[0]) * character->collider.getWidth() / 2 *
                        sinf(character->collider.getAngle()) + pow(-1, y[1]) * character->collider.getHeight() / 2 * cosf(character->collider.getAngle()));

        float theta = atan2f(pt.y - position.y, pt.x - position.x);
        float dist = sqrtf(powf(pt.x - position.x, 2) + powf(pt.y - position.y, 2));

        // minimum distance for the attacker to not attack itself
        auto attackerDistance = sqrt(powf(attackerCollider.getWidth(),2) + powf(attackerCollider.getHeight(),2));

        // check if the vertex is in the range of the weapon
        if (dist > attackerDistance && dist < range && theta > angle - M_PI / 4 && theta < angle + M_PI /4)
            return true;
    }
    return false;
}

