//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_RANGEDWEAPON_H
#define MAIN_CPP_RANGEDWEAPON_H

#include <list>

#include "Weapon.h"
#include "Bullet.h"

enum class RangedWeaponType {
    Rock,
    Straw,
    NaturalWeapon
};

class RangedWeapon : public Weapon {
public:
    // Constructor and Destructor
    explicit RangedWeapon(RangedWeaponType type, std::string name = " ", float damage = 1, float speed = 5,
                          sf::Vector2f dimensions = {.25f, .25f}, bool isTracking = false, bool isShattering = false,
                          ItemRarity rarity = ItemRarity::Common, int price = 50);
    ~RangedWeapon() override = default;

    // Create bullet and puts it on the list
    void useWeapon(FloorMap *floor, GameCharacter *attacker) override;

private:
    // list of bullets' attributes
    float damage, speed;
    sf::Vector2f dimensions;

    // special bullets features
    bool isTracking, isShattering;

    // SFML Sprite of the bullet
    sf::Texture bulletTexture;
    sf::Sprite sprite{bulletTexture};
};


#endif //MAIN_CPP_RANGEDWEAPON_H
