//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_WEAPON_H
#define MAIN_CPP_WEAPON_H

#include <list>

#include "Item.h"

class FloorMap;

class Enemy;

class Weapon : public Item {
public:
    // Constructor and Destructor
    explicit Weapon(std::string name, ItemRarity rarity, int price): Item(std::move(name), rarity, price) {}

    ~Weapon() override = default;

    // overridden in derived classes to attack the nearest enemy or to create a bullet
    virtual void useWeapon(sf::Vector2f playerPosition, float bulletAngle, std::list<std::unique_ptr<Enemy>> &enemyList,
                           float strength, FloorMap *floor) = 0;
};

#endif //MAIN_CPP_WEAPON_H
