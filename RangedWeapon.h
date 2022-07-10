//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_RANGEDWEAPON_H
#define MAIN_CPP_RANGEDWEAPON_H

#include <list>

#include "Weapon.h"
#include "Bullet.h"

class RangedWeapon : public Weapon{
public:
    // Constructor and Destructor
    explicit RangedWeapon(sf::Sprite bulletBody, float damage = 5, float speed = 5, float range = 10,
                          bool isTracking = false,
                          bool isShattering = false, ItemRarity rarity = ItemRarity::Common, std::string name = " ",
                          int price = 50);
    ~RangedWeapon() override = default;

    // Create bullet and puts it on the list
    float useWeapon() override;

private:
    // TODO function that manage bullets


    // List of the bullets shot
    std::list<Bullet> bulletList {};

    // list of the attributes of the Bullet it must create
    float damage;
    float speed;
    float range;
    // Special ability
    bool isTracking;
    bool isShattering;
    // SFML Sprite
    sf::Sprite body;


};


#endif //MAIN_CPP_RANGEDWEAPON_H
