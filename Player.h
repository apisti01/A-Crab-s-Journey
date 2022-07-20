//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include <list>

#include "GameCharacter.h"
#include "Enemy.h"
#include "Wearable.h"
#include "StaticRangedEnemy.h"
#include "Weapon.h"



enum class CrabSpecie {
    BrownCrab,
    AsianPaddleCrab,
    TriangleTannerCrab,
    FiddlerCrab
};

class Player : public GameCharacter {
public:
    // Constructor and Destructor
    Player(const sf::Texture& texture, std::unique_ptr<Weapon> Weapon, CrabSpecie crabSpecie, std::string name = " ",
           float hp = 8, float maxHp = 10, float speed = 2, float maxSpeed = 3, float armor = 0.2, float maxArmor = 0.5,
           float strength = 1.2, float maxStrength = 2, std::string namePlayer =  " ", int coins = 0);
    ~Player() override = default;

    // Update player with user input
    void update(int deltaTime, std::list<std::unique_ptr<Enemy>> &enemyList);

    // move player with user input
    void move(int deltaTime);

    // change angle
    sf::Vector2f rotate(int deltaTime);

    // if left mouse button clicked, delegate to weapon the use
    void attack(std::list<std::unique_ptr<Enemy>> &enemyList, sf::Vector2f bulletCoordinates);

    // take a Wearable and puts it on, return the item wore before
    std::unique_ptr<Wearable> wearItem(std::unique_ptr<Wearable> item);

    // take a Weapon and puts it on, return the weapon wielded before
    std::unique_ptr<Weapon> changeWeapon(std::unique_ptr<Weapon> weapon1);

    // getter of the coins
    int getCoins() const { return coins; }

    // given a value increases the coins
    void receiveCoins(int value) { Player::coins += value; }

private:
    // name of the crab specie
    std::string namePlayer;

    // Specification about the starting statistics
    CrabSpecie crabSpecie;

    // coin owned
    int coins;
    int fps = 10;

    // wearable on the player
    std::unique_ptr<Wearable> hat = nullptr;
    std::unique_ptr<Wearable> shield = nullptr;
    std::unique_ptr<Wearable> shell = nullptr;
};


#endif //MAIN_CPP_PLAYER_H
