//
// Created by apisti01 on 10/07/22.
//

#include "Player.h"

Player::Player(std::string name, CrabSpecie crabSpecie, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> Weapon,
               float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
               float maxStrength, int coins) :
        GameCharacter(std::move(name), texture, collider, std::move(Weapon), hp, maxHp, speed, maxSpeed, armor,
                      maxArmor, strength, maxStrength), crabSpecie(crabSpecie) {
}

void Player::update(int deltaTime, FloorMap *floor, bool clicked) {
    // get keyboard and mouse inputs to move and rotate the player
    sf::Vector2f deltaPos = getKeyboardInput(deltaTime, floor);
    float deltaAngle = getMouseInput(deltaTime);

    deltaPos = updateSpriteAndCollider(deltaPos, deltaAngle, floor);

    selectAnimation(deltaPos);

    // if the player goes through doors, then change room
    changeRoom(floor);

    attack(floor, sprite.getAngle(), clicked);

    // update the animation
    sprite.update(fps, animationBehaviour, deltaTime);

}

sf::Vector2f Player::getKeyboardInput(int deltaTime, FloorMap *floor) {
    sf::Vector2f deltaPos {0, 0};

    // take user input and memorize the movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        deltaPos.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        deltaPos.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        deltaPos.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        deltaPos.x += 1;

    // normalization
    float norm = sqrtf(powf(deltaPos.x, 2) + powf(deltaPos.y, 2));
    if (norm != 0) {
        deltaPos.x = deltaPos.x / norm;
        deltaPos.y = deltaPos.y / norm;
    }
    deltaPos.x = deltaPos.x * speed * sprite.getWidth() * static_cast<float>(deltaTime) / 1000000;
    deltaPos.y = deltaPos.y * speed * sprite.getHeight() * static_cast<float>(deltaTime) / 1000000;

    return deltaPos;
}

float Player::getMouseInput(int deltaTime) {
    // coordinates of the mouse when pressed
    auto coordinates = sf::Mouse::getPosition();

    // coordinates relative to the position of the player
    sf::Vector2f relativeCoordinates {
            float(coordinates.x) - sprite.getPosition().x, float(coordinates.y) - sprite.getPosition().y
    };

    // angle in radians of the position of the mouse relative to the player
    float facingAngle = atan2f(relativeCoordinates.y, relativeCoordinates.x);

    return facingAngle - sprite.getAngle();
}

void Player::changeRoom(FloorMap *floor) {
    // move across map through doors
    // right door
    if (sprite.getPosition().x > floor->roomList[floor->currentRoomIndex].getWidth() && floor->roomList[floor->currentRoomIndex].doors[1] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex].doors[1];
        sprite.setPosition({ 5, sprite.getPosition().y });
    }
    // left door
    if (sprite.getPosition().x < 0 && floor->roomList[floor->currentRoomIndex].doors[3] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex].doors[3];
        sprite.setPosition({ static_cast<float>(floor->roomList[floor->currentRoomIndex].getWidth() - 5), sprite.getPosition().y });
    }
    // bottom door
    if (sprite.getPosition().y > floor->roomList[floor->currentRoomIndex].getHeight() && floor->roomList[floor->currentRoomIndex].doors[2] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex].doors[2];
        sprite.setPosition({ sprite.getPosition().x, 5 });
    }
    // upper door
    if (sprite.getPosition().y < 0 && floor->roomList[floor->currentRoomIndex].doors[0] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex].doors[0];
        sprite.setPosition({ sprite.getPosition().x, static_cast<float>(floor->roomList[floor->currentRoomIndex].getHeight() - 5) });
    }
    collider.setPosX(sprite.getPosition().x);
    collider.setPosY(sprite.getPosition().y);
}

void Player::attack(FloorMap *floor, float bulletAngle, bool clicked) {
    // if player has a weapon and left mouse button is pressed
    if (weapon && clicked) {
        // if ranged it delegates the creation of bullets, return the damage if melee
        // weapon->useWeapon(sprite.getPosition(), bulletAngle, floor->roomList[floor->currentRoomIndex].enemyList, strength, floor);
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
