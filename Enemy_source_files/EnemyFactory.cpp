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

std::list<std::unique_ptr<Enemy>> EnemyFactory::fillRoomWithEnemies(Bestiary* bestiary, Room *room, std::string mapType, int level) {
    std::list<std::unique_ptr<Enemy>> enemyList{};

    // if it's not the boss room
    if (!room->getBossRoom()) {
        // generate a number of normal enemies according to the level
        int numberOfEnemies = static_cast<int>(round(8 - exp(1.8f - float(level) / 4.f)));

        // prepare every enemy
        for (int i = 0; i < numberOfEnemies; ++i) {
            // creation
            auto enemy = selectRandomEnemy(bestiary, mapType, level);
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

std::unique_ptr<Enemy> EnemyFactory::selectRandomEnemy(Bestiary* bestiary, std::string mapType, int level) {
    // pick a random enemy from all the bestiary
    auto enemy = bestiary->beasts[rand() % size(bestiary->beasts)];

    // if this enemy is
    if (std::count(enemy.habitats.begin(), enemy.habitats.end(), mapType)) {
        // the sprite of the enemy instead has to be created, loaded and passed here
        sf::Texture enemyTexture;
        enemyTexture.loadFromFile("GameCharacter/Enemy/" + enemy.type + "/" + enemy.name + "/Texture.png");

        // create the enemy collider
        Collider enemyCollider(float(1920) / 2, float(1080) / 2, enemyTexture.getSize().x * 0.6,
                               enemyTexture.getSize().y * 0.6);

        // create the enemy pointer
        std::unique_ptr<Enemy> enemyPtr;

        if (enemy.type == "AggressiveMelee") {
            // create a weapon
            auto meleeWeapon = make_unique<MeleeWeapon>(MeleeWeaponType::NaturalWeapon, "Natural Weapon");
            // create the enemy
            auto ame = std::make_unique<AggressiveMeleeEnemy>(enemy.id, enemy.name, enemyTexture, enemyCollider,
                                                              std::move(meleeWeapon), enemy.health, enemy.health,
                                                              enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                              enemy.strength, enemy.strength, 10, 10, 10,
                                                              enemy.attackTimer, enemy.triggerRange);
            enemyPtr = std::move(ame);
        }

        else if (enemy.type == "ChasingRanged") {
            // create a weapon
            auto rangedWeapon = make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon, "Natural Weapon");
            // create the enemy
            auto cre = std::make_unique<ChasingRangedEnemy>(enemy.id, enemy.name, enemyTexture, enemyCollider,
                                                            std::move(rangedWeapon), enemy.health, enemy.health,
                                                            enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                            enemy.strength, enemy.strength, 10, 10, 10,
                                                            enemy.attackTimer, enemy.triggerRange);
            enemyPtr = std::move(cre);
        }

        else if (enemy.type == "DefensiveMelee") {
            // create a weapon
            auto meleeWeapon = make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon, "Natural Weapon");
            // create the enemy
            auto dme = std::make_unique<DefensiveMeleeEnemy>(enemy.id, enemy.name, enemyTexture, enemyCollider,
                                                             std::move(meleeWeapon), enemy.health, enemy.health,
                                                             enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                             enemy.strength, enemy.strength, 10, 10, 10,
                                                             enemy.attackTimer, enemy.triggerRange);
            enemyPtr = std::move(dme);
        }

        else if (enemy.type == "StaticRanged") {
            // create a weapon
            auto rangedWeapon = make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon, "Natural Weapon");
            // create the enemy
            auto sre = std::make_unique<StaticRangedEnemy>(enemy.id, enemy.name, enemyTexture, enemyCollider,
                                                           std::move(rangedWeapon), enemy.health, enemy.health,
                                                           enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                           enemy.strength, enemy.strength, 10, 10, 10,
                                                           enemy.attackTimer);
            enemyPtr = std::move(sre);
        }

        return enemyPtr;
    } else {
        return selectRandomEnemy(bestiary, mapType, level);
    }
}

void EnemyFactory::placeEnemy(Enemy *enemy, Room *room) {
    // get one free spot on room grid coordinates
    sf::Vector2i pos = room->pickFreeGridSpot();

    // and place the enemy there
    enemy->setPosition(pos.x, pos.y);
}