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
    explicit RangedWeapon(const sf::Texture& bulletBody, float damage = 5, float speed = 5, float range = 10,
                          bool isTracking = false,
                          bool isShattering = false, ItemRarity rarity = ItemRarity::Common, std::string name = " ",
                          int price = 50);
    ~RangedWeapon() override = default;

    // Create bullet and puts it on the list
    void useWeapon(sf::Vector2f playerPosition, float bulletAngle, std::list<std::unique_ptr<Enemy>> &enemyList,
                   float strength, FloorMap *floor) override;

private:

    // list of bullets' attributes
    float damage;
    float speed;
    float range;

    // special bullets features
    bool isTracking;
    bool isShattering;

    // SFML Sprite of the bullet
    sf::Texture bulletTexture;
    sf::Sprite sprite {bulletTexture};
};


#endif //MAIN_CPP_RANGEDWEAPON_H
