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

    // if it's not the boss room
    if (!room->getBossRoom()) {
        // generate a number of normal enemies according to the level
        int numberOfEnemies = static_cast<int>(round(8 - exp(1.8f - float(level) / 4.f)));

        // prepare every enemy
        for (int i = 0; i < numberOfEnemies; ++i) {
            // creation
            auto enemy = createSingleEnemy(type, level);
            // setting position
            placeEnemy(enemy.get(), room);
            //adding to the list
            enemyList.push_back(std::move(enemy));
        }
    } else { // if it is the boss room
        // TODO create the boss
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

void EnemyFactory::placeEnemy(Enemy *enemy, Room *room) {
    // get one free spot on room grid coordinates
    sf::Vector2i pos = room->pickFreeGridSpot();

    // TODO: if enemy is a defensive melee enemy set its origin position

    // and place the enemy there
    enemy->setPosition(pos.x, pos.y);
}

std::unique_ptr<Enemy> EnemyFactory::coralReefEnemy(int level) {
    std::unique_ptr<Enemy> enemy;

    // random type of behaviour type
    int type = rand() % 4;

    // TODO if there are more than 1 enemy type per behaviour per habitat then do another switch inside
    switch (type) {
        case 0: // Static ranged
        {
            // the sprite of the bullet of the ranged weapon is directly loaded in the constructor of the weapon
            auto weapon = make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon, "Natural Weapon");
            // the sprite of the enemy instead has to be created, loaded and passed here
            sf::Texture enemyTexture;
            enemyTexture.loadFromFile("GameCharacter/Enemy/Static Ranged/Hermit Crab/Texture.png");

            // and a collider
            Collider enemyCollider(float (1920) / 2, float (1080) / 2,
                                   enemyTexture.getSize().x * 0.6,
                                   enemyTexture.getSize().y * 0.6);
            auto tmp = std::make_unique<StaticRangedEnemy>("Hermit Crab", enemyTexture, enemyCollider, std::move(weapon),
                                                           10, 10, 1, 1, 3, 3, 10, 10, 10, 10, 10);
            // move to the pointer that is then returned
            enemy = std::move(tmp);

            break;
        }
        case 1: // Chasing ranged
        {
            // the sprite of the bullet of the ranged weapon is directly loaded in the constructor of the weapon
            auto weapon = make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon, "Natural Weapon");
            // the sprite of the enemy instead has to be created, loaded and passed here
            sf::Texture enemyTexture;
            enemyTexture.loadFromFile("GameCharacter/Enemy/Chasing Ranged/Squid/Texture.png");

            // and a collider
            Collider enemyCollider(float (1920) / 2, float (1080) / 2,
                                   enemyTexture.getSize().x * 0.6,
                                   enemyTexture.getSize().y * 0.6);
            int triggerRange = 360;
            auto tmp = std::make_unique<ChasingRangedEnemy>("Squid", enemyTexture, enemyCollider, std::move(weapon),
                                                            10, 10, 1, 1, 2, 2, 10, 10, 10, 10, 10, triggerRange);
            // move to the pointer that is then returned
            enemy = std::move(tmp);

            break;
        }
        case 2: // Aggressive melee
        {
            // the sprite of the bullet of the ranged weapon is directly loaded in the constructor of the weapon
            auto weapon = make_unique<MeleeWeapon>(MeleeWeaponType::NaturalWeapon, "Natural Weapon");
            // the sprite of the enemy instead has to be created, loaded and passed here
            sf::Texture enemyTexture;
            enemyTexture.loadFromFile("GameCharacter/Enemy/Aggressive Melee/Sea Turtle/Texture.png");

            // and a collider
            Collider enemyCollider(float (1920) / 2, float (1080) / 2,
                                   enemyTexture.getSize().x * 0.6,
                                   enemyTexture.getSize().y * 0.6);
            int triggerRange = 180;
            auto tmp = std::make_unique<AggressiveMeleeEnemy>("Sea Turtle", enemyTexture, enemyCollider, std::move(weapon),
                                                              10, 10, 1, 1, 4, 4, 10, 10, 10, 10, 10, triggerRange);
            // move to the pointer that is then returned
            enemy = std::move(tmp);

            break;
        }
        case 3: // Defensive melee
        {
            // the sprite of the bullet of the ranged weapon is directly loaded in the constructor of the weapon
            auto weapon = make_unique<MeleeWeapon>(MeleeWeaponType::NaturalWeapon, "Natural Weapon");
            // the sprite of the enemy instead has to be created, loaded and passed here
            sf::Texture enemyTexture;
            enemyTexture.loadFromFile("GameCharacter/Enemy/Defensive Melee/Puffer Fish/Texture.png");

            // and a collider
            Collider enemyCollider(float (1920) / 2, float (1080) / 2,
                                   enemyTexture.getSize().x * 0.6,
                                   enemyTexture.getSize().y * 0.6);
            int triggerRange = 240;
            auto tmp = std::make_unique<DefensiveMeleeEnemy>("Puffer Fish", enemyTexture, enemyCollider, std::move(weapon),
                                                             10, 10, 0.6, 0.6, 2, 2, 10, 10, 10, 10, 10, triggerRange);
            // move to the pointer that is then returned
            enemy = std::move(tmp);

            break;
        }
    }

    return enemy;
}

std::unique_ptr<Enemy> EnemyFactory::mangroveForestEnemy(int level) {
    std::unique_ptr<Enemy> enemy;
    return enemy;
}

std::unique_ptr<Enemy> EnemyFactory::temperateReefEnemy(int level) {
    std::unique_ptr<Enemy> enemy;
    return enemy;
}

std::unique_ptr<Enemy> EnemyFactory::kelpForestEnemy(int level) {
    std::unique_ptr<Enemy> enemy;
    return enemy;
}

std::unique_ptr<Enemy> EnemyFactory::posidoniaMeadowEnemy(int level) {
    std::unique_ptr<Enemy> enemy;
    return enemy;
}

std::unique_ptr<Enemy> EnemyFactory::iceFloeEnemy(int level) {
    std::unique_ptr<Enemy> enemy;
    return enemy;
}


