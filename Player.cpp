//
// Created by apisti01 on 10/07/22.
//

#include "Player.h"

Player::Player(const sf::Texture& texture, std::unique_ptr<Weapon> Weapon, CrabSpecie crabSpecie, std::string name,
               float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
               float maxStrength, std::string namePlayer, int coins) :
        GameCharacter(texture, std::move(name), hp, maxHp, speed, maxSpeed, armor, maxArmor, strength, maxStrength,
                      std::move(Weapon)), namePlayer(std::move(namePlayer)), crabSpecie(crabSpecie), coins(coins) {
}

void Player::update(int deltaTime, std::list<std::unique_ptr<Enemy>> &enemyList) {
    // first get the input for directions, facing and shooting from the mouse
    mouseInput(deltaTime, enemyList);

    // the get the input from the keyboard to move the entity
    move(deltaTime);

    // update the animation
    sprite.update(fps, animationBehaviour, deltaTime);

    // if the weapon is ranged
    if (weapon) {
        // move the bullets
        weapon->update(deltaTime);
    }
}

void Player::mouseInput(int deltaTime, std::list<std::unique_ptr<Enemy>> &enemyList) {
    const float PI = 3.14159265;

    // coordinates of the mouse when pressed
    auto coordinates = sf::Mouse::getPosition();

    // coordinates relative to the position of the player
    sf::Vector2f relativeCoordinates {
            float(coordinates.x) - sprite.getPosition().x, float(coordinates.y) - sprite.getPosition().y
    };

    // angle in degrees of the position of the mouse relative to the player
    auto result = float(atan2(-relativeCoordinates.y, relativeCoordinates.x) * 180 / PI);

    // result corrected for the rotated and inverted plane of SFML
    result = 90 - result;

    // changing the angle the sprite is facing
    sprite.changeAngle(result);

    if (weapon) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            // delegate attack both with melee or the creation of bullet with ranged
            attack(enemyList, relativeCoordinates);
        }
    }
}

void Player::attack(std::list<std::unique_ptr<Enemy>> &enemyList, sf::Vector2f coordinates) {
    // if ranged it delegates the creation of bullets, return the damage if melee
    auto damage = weapon->useWeapon(sprite.getPosition(), coordinates) * strength;

    // if melee then it searches for the first enemy in range and gives it damage
    if (typeid(weapon.get()) == typeid(MeleeWeapon*)) {
        // find the first available enemy
        for (auto enemy = enemyList.begin(); enemy != enemyList.end(); enemy++) {
            if (checkEnemy(enemy->get())) {
                (*enemy)->receiveDamage(damage);
                break;
            }
        }
    }
}

bool Player::checkEnemy(const Enemy *enemy) {
    return false;
}

void Player::move(int deltaTime) {
    sf::Vector2f deltaPos {0, 0};

    // take user input and memorize the movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        deltaPos.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        deltaPos.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        deltaPos.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        deltaPos.x = 1;

    // normalization
    float norm = sqrtf(powf(deltaPos.x, 2) + powf(deltaPos.y, 2));
    if (norm != 0) {
        deltaPos.x = deltaPos.x / norm;
        deltaPos.y = deltaPos.y / norm;
    }
    deltaPos.x = deltaPos.x * speed * sprite.getWidth() * deltaTime / 1000000;
    deltaPos.y = deltaPos.y * speed * sprite.getHeight() * deltaTime / 1000000;

    // selection of animation: supposing the player is standing still
    animationBehaviour = 0;
    // TODO: selection based of its angle and movement direction
    if (deltaPos.x != 0 || deltaPos.y != 0)
        animationBehaviour = 1;

    // move the sprite
    sprite.move(deltaPos.x, deltaPos.y);
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
