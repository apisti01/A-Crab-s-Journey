//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H


#include "GameCharacter.h"
#include "Enemy.h"
#include "Wearable.h"
#include "StaticRangedEnemy.h"

enum class CrabSpecie{
    BrownCrab,
    AsianPaddleCrab,
    TriangleTannerCrab,
    FiddlerCrab
};

class Player : public GameCharacter{
public:
    // Constructor and Destructor
    Player(const sf::Texture& texture, std::unique_ptr<Weapon> Weapon, CrabSpecie crabSpecie, std::string name = " ", float hp = 10,
           float maxHp = 10, float speed = 10, float maxSpeed = 10, float armor = 10, float maxArmor = 10, float strength = 10, float maxStrength = 10,
           std::string namePlayer =  " ", int coins = 0);
    ~Player() override = default;

    // Update player with user input
    void update(int deltaTime, std::list<std::unique_ptr<Enemy>> &enemyList);

    // move player with user input
    void move(int deltaTime);

    // change angle and attack
    void mouseInput(int deltaTime, std::list<std::unique_ptr<Enemy>> &enemyList);

    // if weapon is ranged create bullet, if melee find the first in range enemy and gives it damages
    void attack(std::list<std::unique_ptr<Enemy>> &enemyList, sf::Vector2f coordinates);

    // TODO
    bool checkEnemy(const Enemy *enemy);

    // Take a Wearable and puts it on, return the item wore before
    std::unique_ptr<Wearable> wearItem(std::unique_ptr<Wearable> item);

    // TAke a Weapon and puts it on, return the weapon wielded before
    std::unique_ptr<Weapon> changeWeapon(std::unique_ptr<Weapon> weapon1);

private:
    std::string namePlayer;

    // Specification about the starting statistics
    CrabSpecie crabSpecie;

    int coins;

    // Wearable on the player
    std::unique_ptr<Wearable> hat = nullptr;
    std::unique_ptr<Wearable> shield = nullptr;
    std::unique_ptr<Wearable> shell = nullptr;

};


#endif //MAIN_CPP_PLAYER_H
