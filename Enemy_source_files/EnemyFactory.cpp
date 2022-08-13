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
            int numberOfEnemies = static_cast<int>(round(8 - exp(1.8f - float(level) / 4.f)));

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
    std::unique_ptr<Enemy> enemy;

    switch (mapType) {
        case MapType::CoralReef:
            enemy = coralReefEnemy(level);
            break;
        case MapType::MangroveForest:
            enemy = mangroveForestEnemy(level);
            break;
        case MapType::TemperateReef:
            enemy = temperateReefEnemy(level);
            break;
        case MapType::KelpForest:
            enemy = kelpForestEnemy(level);
            break;
        case MapType::PosidoniaMeadow:
            enemy = posidoniaMeadowEnemy(level);
            break;
        case MapType::IceFloe:
            enemy = iceFloeEnemy(level);
            break;
    }

    return enemy;
}

void EnemyFactory::locateEnemy(Enemy *enemy, Room *room) {

    // TODO  assign a random position in the grid, check with the appropriate function if the position is occupied by walls or obstacles
    //  and then if is it already occupied by another enemy
}

std::unique_ptr<Enemy> EnemyFactory::coralReefEnemy(int level) {
    std::unique_ptr<Enemy> enemy;

    // random type of behaviour type
    int type = rand()%4;

    switch (type) {
        case 0: // Static ranged
        {
            // TODO if there are more than 1 enemy type per behaviour per habitat then do another switch inside

            // the sprite of the bullet of the ranged weapon is directly loaded in the constructor of the weapon
            auto weapon = make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon, "Natural Weapon");
            // the sprite of the enemy instead has to be created, loaded and passed here
            // TODO load enemy texture, and create collider
            auto tmp = std::make_unique<StaticRangedEnemy>("carlo", sf::Texture(), Collider(), std::move(weapon), 10,
                                                           10, 10, 10, 10, 10, 10, 10, 10);
            // move to the pointer that is then returned
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
