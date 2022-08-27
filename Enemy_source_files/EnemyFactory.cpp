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

std::list<std::unique_ptr<Enemy>> EnemyFactory::fillRoomWithEnemies(Bestiary* bestiary, Room *room, MapType type, int level) {
    std::list<std::unique_ptr<Enemy>> enemyList{};

    // if it's not the boss room
    if (!room->getBossRoom()) {
        // generate a number of normal enemies according to the level
        int numberOfEnemies = static_cast<int>(round(8 - exp(1.8f - float(level) / 4.f)));

        // prepare every enemy
        for (int i = 0; i < numberOfEnemies; ++i) {
            // creation
            auto enemy = selectRandomEnemy(bestiary, type, level);
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

std::unique_ptr<Enemy> EnemyFactory::selectRandomEnemy(Bestiary* bestiary, MapType mapType, int level) {
    // pick a random enemy from all the bestiary
    auto enemy = bestiary->beasts[rand() % size(bestiary->beasts)];

    std::string habitat;
    switch (mapType) {
        case MapType::CoralReef:
            habitat = "CoralReef";
            break;
        case MapType::MangroveForest:
            habitat = "MangroveForest";
            break;
        case MapType::TemperateReef:
            habitat = "TemperateReef";
            break;
        case MapType::KelpForest:
            habitat = "KelpForest";
            break;
        case MapType::PosidoniaMeadow:
            habitat = "PosidoniaMeadow";
            break;
        case MapType::IceFloe:
            habitat = "IceFloe";
            break;
    }

    // if this enemy is
    if (std::count(enemy.habitats.begin(), enemy.habitats.end(), habitat)) {
        // assing a weapon
        auto rangedWeapon = make_unique<RangedWeapon>(RangedWeaponType::NaturalWeapon, "Natural Weapon");
        auto meleeWeapon = make_unique<MeleeWeapon>(MeleeWeaponType::NaturalWeapon, "Natural Weapon");

        // the sprite of the enemy instead has to be created, loaded and passed here
        sf::Texture enemyTexture;
        enemyTexture.loadFromFile("GameCharacter/Enemy/" + enemy.type + "/" + enemy.name + "/Texture.png");

        // and a collider
        Collider enemyCollider(float(1920) / 2, float(1080) / 2, enemyTexture.getSize().x * 0.6,
                               enemyTexture.getSize().y * 0.6);

        auto ame = std::make_unique<AggressiveMeleeEnemy>(enemy.name, enemyTexture, enemyCollider,
                                                          std::move(meleeWeapon), enemy.health, enemy.health,
                                                          enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                          enemy.strength, enemy.strength, 10, 10, 10,
                                                          enemy.triggerRange);
        auto cre = std::make_unique<ChasingRangedEnemy>(enemy.name, enemyTexture, enemyCollider,
                                                        std::move(rangedWeapon), enemy.health, enemy.health,
                                                        enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                        enemy.strength, enemy.strength, 10, 10, 10,
                                                        enemy.triggerRange);
        auto dme = std::make_unique<DefensiveMeleeEnemy>(enemy.name, enemyTexture, enemyCollider,
                                                         std::move(meleeWeapon), enemy.health, enemy.health,
                                                         enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                         enemy.strength, enemy.strength, 10, 10, 10,
                                                         enemy.triggerRange);
        auto sre = std::make_unique<StaticRangedEnemy>(enemy.name, enemyTexture, enemyCollider,
                                                       std::move(rangedWeapon), enemy.health, enemy.health,
                                                       enemy.speed, enemy.speed, enemy.armor, enemy.armor,
                                                       enemy.strength, enemy.strength, 10, 10, 10);

        std::unique_ptr<Enemy> enemyPtr;
        if (enemy.type == "AggressiveMelee")
            enemyPtr = std::move(ame);
        else if (enemy.type == "ChasingRanged")
            enemyPtr = std::move(cre);
        else if (enemy.type == "DefensiveMelee")
            enemyPtr = std::move(dme);
        else if (enemy.type == "StaticRanged")
            enemyPtr = std::move(sre);

        return enemyPtr;
    } else {
        return selectRandomEnemy(bestiary, mapType, level);
    }
}

void EnemyFactory::placeEnemy(Enemy *enemy, Room *room) {
    // get one free spot on room grid coordinates
    sf::Vector2i pos = room->pickFreeGridSpot();

    // TODO: if enemy is a defensive melee enemy set its origin position

    // and place the enemy there
    enemy->setPosition(pos.x, pos.y);
}