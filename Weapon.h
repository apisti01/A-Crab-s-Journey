//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_WEAPON_H
#define MAIN_CPP_WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
    // Constructor and Destructor
    explicit Weapon(std::string name, ItemRarity rarity, int price);
    ~Weapon() override = default;

    virtual float useWeapon(sf::Vector2f playerPosition, sf::Vector2f bulletDirections) = 0;

    virtual void update(int deltaTime) = 0;

    // overridden only to draw bullets
    virtual void draw(sf::RenderWindow& window) = 0;

};


#endif //MAIN_CPP_WEAPON_H
