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
    // get keyboard and mouse inputs to move and rotate the player
    move(deltaTime);
    auto direction = rotate(deltaTime);

    attack(enemyList, direction );

    // update the animation
    sprite.update(fps, animationBehaviour, deltaTime);

    // if the weapon is ranged
    if (weapon) {
        // move the bullets
        weapon->update(deltaTime);
    }
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
    deltaPos.x = deltaPos.x * speed * sprite.getWidth() * static_cast<float>(deltaTime) / 1000000;
    deltaPos.y = deltaPos.y * speed * sprite.getHeight() * static_cast<float>(deltaTime) / 1000000;

    // suppose the player is standing still
    animationBehaviour = 0;
    // if player is moving
    if (deltaPos.x != 0 || deltaPos.y != 0) {
        // calculate the two angles
        float velocityAngle = atan2f(deltaPos.y, deltaPos.x);
        float facingAngle = sprite.getAngle();
        float diff = fabsf(velocityAngle - facingAngle);

        // determine the animation based on the angle difference
        if (sinf(diff) > sqrtf(2) / 2 || sinf(diff) < -sqrtf(2) / 2) {
            // horizontal movement
            animationBehaviour = 1;
        } else {
            // vertical movement
            animationBehaviour = 2;
        }
    }

    // move the sprite
    sprite.move(deltaPos.x, deltaPos.y);
}

sf::Vector2f Player::rotate(int deltaTime) {
    // coordinates of the mouse when pressed
    auto coordinates = sf::Mouse::getPosition();

    // coordinates relative to the position of the player
    sf::Vector2f relativeCoordinates {
            float(coordinates.x) - sprite.getPosition().x, float(coordinates.y) - sprite.getPosition().y
    };

    // angle in radians of the position of the mouse relative to the player
    float facingAngle = atan2f(relativeCoordinates.y, relativeCoordinates.x);

    // changing the angle the sprite is facing
    sprite.setAngle(facingAngle);

    // total distance between the player and the mouse
    auto distance = sqrtf(powf(relativeCoordinates.x,2) + powf(relativeCoordinates.y,2));

    // normalized coordinates
    relativeCoordinates.x /= distance;
    relativeCoordinates.y /= distance;

    // get the normalized coordinates back to keep memory of the trajectory of the mouse
    return relativeCoordinates;
}

void Player::attack(std::list<std::unique_ptr<Enemy>> &enemyList, sf::Vector2f bulletCoordinates) {
    // if player has a weapon and left mouse button is pressed
    if (weapon && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        // if ranged it delegates the creation of bullets, return the damage if melee
        weapon->useWeapon(sprite.getPosition(), bulletCoordinates, enemyList, strength);
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
