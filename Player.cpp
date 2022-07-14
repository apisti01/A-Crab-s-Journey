//
// Created by apisti01 on 10/07/22.
//

#include "Player.h"


Player::Player(const sf::Texture& texture, std::unique_ptr<Weapon> Weapon, CrabSpecie crabSpecie, std::string name, float hp,
               float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength, float maxStrength,
               std::string namePlayer, int coins) :
        GameCharacter(texture, std::move(name), hp, maxHp, speed, maxSpeed, armor, maxArmor, strength,
                      maxStrength, std::move(Weapon)),
        namePlayer(std::move(namePlayer)), crabSpecie(crabSpecie), coins(coins) {
}

void Player::attack(std::list<std::unique_ptr<Enemy>> &enemyList, sf::Vector2f coordinates) {
    // if ranged it delegates the creation of bullets, return the damage if melee
    auto damage = weapon->useWeapon(sprite.getPosition(), coordinates) * strength;

    // if melee then it searches for the first enemy in range and gives it damage
    if (typeid(weapon.get()) == typeid(MeleeWeapon*)) {
        // find the first available enemy
        for (auto enemy = enemyList.begin(); enemy != enemyList.end(); enemy++) {
            if (checkEnemy(enemy->get())){
                (*enemy)->receiveDamage(damage);
                break;
            }
        }
    }
}

std::unique_ptr<Wearable> Player::wearItem(std::unique_ptr<Wearable> item) {
    std::unique_ptr<Wearable> tmp = nullptr;

    // different types of wearable player can have
    switch (item->getType()) {
        case WearablePieces::Hat:
            tmp = std::move(hat);
            hat = std::move(item);
            break;
        case WearablePieces::Shield:
            tmp = std::move(shield);
            shield = std::move(item);
            break;
        case WearablePieces::Shell:
            tmp = std::move(shell);
            shell = std::move(item);
            break;
    }

    // gives back the object wore before
    return tmp;
}

std::unique_ptr<Weapon> Player::changeWeapon(std::unique_ptr<Weapon> weapon1) {
    auto tmp = std::move(weapon);
    // move the weapon in
    weapon = std::move(weapon1);
    // gives back the old weapon
    return tmp;
}

void Player::move(int deltaTime) {
    // start supposing the player is standing still
    animationBehaviour = 0;
    float x = 0;
    float y = 0;

    // take user input and memorize the movement, also change the row of the animation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        y -= speed * float (deltaTime);
        animationBehaviour = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        x -= speed * float(deltaTime);
        animationBehaviour = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        y += speed * float(deltaTime);
        animationBehaviour = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        x += speed * float (deltaTime);
        animationBehaviour = 1;
    }

    // move the sprite
    sprite.move(x, y);
}

void Player::mouseInput(int deltaTime, std::list<std::unique_ptr<Enemy>> &enemyList) {
    const float PI = 3.14159265;

    // coordinates of the mouse when pressed
    auto coordinates = sf::Mouse::getPosition();

    // coordinates relative to the position of the player
    sf::Vector2f relativeCoordinates {float(coordinates.x) - (sprite.getPosition().x + sprite.getWidth()), float(coordinates.y) - (sprite.getPosition().y + sprite.getHeight())};

    // total distance between the player and the mouse
    auto distance = sqrtf(powf(relativeCoordinates.x,2) + powf(relativeCoordinates.y,2));

    // sin and cos
    relativeCoordinates.x /= distance;
    relativeCoordinates.y /= distance;

    // angle in degrees of the position of the mouse relative to the player
    auto result = float (atan2 (- relativeCoordinates.y,relativeCoordinates.x) * 180 / PI) ;

    // result corrected for the rotated and inverted plane of SFML
    result = 90 - result;

    // changing the angle the sprite is facing
    sprite.changeAngle(result);

    if (weapon){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            // delegate attack both with melee or the creation of bullet with ranged
            attack(enemyList, relativeCoordinates);
        }
    }
}

void Player::update(int deltaTime, std::list<std::unique_ptr<Enemy>> &enemyList) {

    // first get the input for directions, facing and shooting from the mouse
    mouseInput(deltaTime,enemyList);

    // the get the input from the keyboard to move the entity
    move(deltaTime);

    // update the animation
    sprite.update(100, animationBehaviour,deltaTime);

    // move the bullets if there are any
    if (weapon){
        weapon->update(deltaTime);
    }
}

bool Player::checkEnemy(const Enemy *enemy) {
    return false;
}
