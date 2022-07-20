//
// Created by apisti01 on 10/07/22.
//

#include "Enemy.h"

Enemy::Enemy(std::string name, std::unique_ptr<Weapon> weapon, float hp, float maxHp, float speed, float maxSpeed,
             float armor, float maxArmor, float strength, float maxStrength, float xpReward, int coinsDropped,
             int pearlsDropped) :
        GameCharacter(std::move(name), sf::Texture(), Collider(0, 0, 0, 0, 0), std::unique_ptr<Weapon>(),
                hp, maxHp, speed, maxSpeed, armor, maxArmor, strength, maxStrength), XpReward(xpReward),
                coinsDropped(coinsDropped), pearlsDropped(pearlsDropped) {}
