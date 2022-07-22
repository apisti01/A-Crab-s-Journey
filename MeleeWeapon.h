//
// Created by apisti01 on 07/07/22.
//

#ifndef MAIN_CPP_MELEEWEAPON_H
#define MAIN_CPP_MELEEWEAPON_H

#include "Weapon.h"
#include "Enemy.h"

class MeleeWeapon : public Weapon{
public:
    // Constructor and Destructor
    explicit MeleeWeapon(float damage, std::string name = " ", ItemRarity rarity = ItemRarity::Common, int price = 50);
    ~MeleeWeapon() override = default;

    // attack the nearest available enemy
    void useWeapon(sf::Vector2f playerPosition, float bulletAngle,
                   std::list<std::unique_ptr<Enemy>> &enemyList, float strength) override;

    // empty because it does not have to draw bullets
    void update(int deltaTime) override {}
    void draw(sf::RenderWindow &window) override{}


    // TODO: write definition for the selection of hit enemy
    bool checkEnemy(const Enemy *enemy);

private:
    // Damage dealt with the attack
    float damage;
};


#endif //MAIN_CPP_MELEEWEAPON_H
