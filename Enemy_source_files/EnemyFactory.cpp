//
// Created by apisti01 on 04/08/22.
//

#include "EnemyFactory.h"
#include "../MeleeWeapon.h"
#include "../RangedWeapon.h"
#include "StaticRangedEnemy.h"
#include "ChasingRangedEnemy.h"
#include "AggressiveMeleeEnemy.h"
#include "DefensiveMeleeEnemy.h"

#include <cstdlib>

std::list<std::unique_ptr<Enemy>> EnemyFactory::fillRoomWithEnemies(Room *room, MapType type, int level) {
    std::list<std::unique_ptr<Enemy>> enemyList{};

    // fill every room apart from the start room
    if (!room->getStartRoom()){

        if (!room->getBossRoom()) { // normal enemies if it isn't the boss room
            // the number of enemies in a single room, increases on the level
            int numberOfEnemies = static_cast<int>(round(9 - exp(1.8f - float(level) / 4.f)));

            // prepare every enemy
            for (int i = 0; i < numberOfEnemies; ++i) {
                // creation
                auto enemy = createSingleEnemy(type,level);
                // setting position
                locateEnemy(enemy.get(), room);
                //adding to the list
                enemyList.push_back(std::move(enemy));
            }
        }else{ // if it is the boss room
            // TODO create the boss

        }
    }

    return enemyList;
}

std::unique_ptr<Enemy> EnemyFactory::createSingleEnemy(MapType mapType, int level) {
    std::unique_ptr<Enemy> enemy = nullptr;

    // random type of behaviour type
    int type = rand()%4;

    switch (type) {
        case 0: // Static ranged
        {
            auto weapon = make_unique<MeleeWeapon>(5, 10);
            auto tmp = std::make_unique<StaticRangedEnemy>("carlo", sf::Texture(), Collider(), std::move(weapon), 10,
                                                           10, 10, 10, 10, 10, 10, 10, 10);
            enemy = std::move(tmp);
            break;
        }
        case 1: // Chasing ranged
            break;
        case 2: // Aggressive melee
            break;
        case 3: // Defensive melee
            break;
    }

    return enemy;
}
