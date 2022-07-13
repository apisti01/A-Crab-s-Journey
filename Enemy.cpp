//
// Created by apisti01 on 10/07/22.
//

#include "Enemy.h"

Enemy::Enemy(std::string name, float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor,
             float strength, float maxStrength, std::unique_ptr<Weapon> weapon, float xpReward, int coinsDropped,
             int pearlsDropped) :
        GameCharacter(sf::Texture(), std::move(name), hp, maxHp, speed, maxSpeed, armor, maxArmor, strength,
                      maxStrength, std::move(weapon)),
             XpReward(xpReward), coinsDropped(coinsDropped), pearlsDropped(pearlsDropped) {}
