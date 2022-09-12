//
// Created by apisti01 on 10/07/22.
//

#include "Player.h"

Player::Player(int characterIndex, std::string name, CrabSpecie crabSpecie, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
               float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
               float maxStrength, float units) :
        GameCharacter(std::move(name), texture, std::move(collider), std::move(weapon), hp, maxHp, speed, maxSpeed, armor,
                      maxArmor, strength, maxStrength, sf::Vector2u(6, 3), units), characterIndex(characterIndex), crabSpecie(crabSpecie) {
}

void Player::update(int deltaTime, FloorMap *floor, bool clicked, sf::RenderWindow &window) {
    // get keyboard and mouse inputs to move and rotate the player
    sf::Vector2f deltaPos = getKeyboardInput(deltaTime, floor);
    float deltaAngle = getMouseInput(deltaTime, window);

    updateColliderAndSprite(deltaPos, deltaAngle, floor);

    selectAnimation();

    // if the player goes through doors, then change room
    changeRoom(floor);
    // check for room's cage status
    checkCageStatus(floor);

    // player can attack only if room is in cage mode
    if (floor->roomList[floor->currentRoomIndex]->getCage())
        attack(floor, clicked);

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
    deltaPos.x = deltaPos.x * speed * Game::getInstance()->getUnit() * float(deltaTime) / pow(10, 6);
    deltaPos.y = deltaPos.y * speed * Game::getInstance()->getUnit() * float(deltaTime) / pow(10, 6);

    return deltaPos;
}

float Player::getMouseInput(int deltaTime, sf::RenderWindow &window) {
    // coordinates of the mouse when pressed
    auto coordinates = sf::Mouse::getPosition(window);

    // coordinates relative to the position of the player
    sf::Vector2f relativeCoordinates {float(coordinates.x) - sprite.getPosition().x, float(coordinates.y) - sprite.getPosition().y};

    // angle in radians of the position of the mouse relative to the player
    float facingAngle = atan2f(relativeCoordinates.y, relativeCoordinates.x);

    return facingAngle - sprite.getAngle();
}

void Player::changeRoom(FloorMap* floor) {
    // move across map through doors
    // right door
    if (collider.getPosX() > floor->roomList[floor->currentRoomIndex]->getWidth() &&
        floor->roomList[floor->currentRoomIndex]->doors[1] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex]->doors[1];
        collider.setPosX(5.f);
    }
    // left door
    if (collider.getPosX() < 0 && floor->roomList[floor->currentRoomIndex]->doors[3] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex]->doors[3];
        collider.setPosX(floor->roomList[floor->currentRoomIndex]->getWidth() - 5.f);
    }
    // bottom door
    if (collider.getPosY() > floor->roomList[floor->currentRoomIndex]->getHeight() &&
        floor->roomList[floor->currentRoomIndex]->doors[2] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex]->doors[2];
        collider.setPosY(5.f);
    }
    // upper door
    if (collider.getPosY() < 0 && floor->roomList[floor->currentRoomIndex]->doors[0] != -1) {
        floor->currentRoomIndex = floor->roomList[floor->currentRoomIndex]->doors[0];
        collider.setPosY(floor->roomList[floor->currentRoomIndex]->getHeight() - 5.f);
    }

    floor->roomList[floor->currentRoomIndex]->setVisited(true);

    sprite.setPosition(collider.getPosition());
}

void Player::checkCageStatus(FloorMap *floor) {
    // if player enter the room and there are enemies
    if (collider.getPosX() > 120 && collider.getPosX() < 1920 - 120 &&
        collider.getPosY() > 120 && collider.getPosY() < 1080 - 120 &&
        size(floor->roomList[floor->currentRoomIndex]->enemyList) != 0 &&
        !floor->roomList[floor->currentRoomIndex]->getCage()) {

        // add obstacles to the doors
        floor->roomList[floor->currentRoomIndex]->setCage(true);
        // update the observers
        floor->notifyObserver(floor->roomList[floor->currentRoomIndex].get());
    }

    // if the room is cleared
    else if (size(floor->roomList[floor->currentRoomIndex]->enemyList) == 0 && floor->roomList[floor->currentRoomIndex]->getCage()) {
        // TOOO: remove the obstacles from the doors
        floor->roomList[floor->currentRoomIndex]->setCage(false);

        // TODO: receive coins and pearls from completing the room
    }
}

void Player::attack(FloorMap *floor, bool clicked) {
    // if player has a weapon and left mouse button is pressed
    if (weapon && clicked) {
        // if ranged it delegates the creation of bullets, if melee deal the damage to all the character in the hit zone
        weapon->useWeapon(floor, this);
    }
}

std::unique_ptr<Wearable> Player::wearItem(std::unique_ptr<Wearable> item) {
    std::unique_ptr<Wearable> tmp = nullptr;

    // add the stats from the new item worn
    if (item)
        modifyStatistics(item.get(), true);

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
    // remove the statistics given by the item wore before
    if (tmp)
        modifyStatistics(tmp.get(), false);

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

void Player::modifyStatistics(Wearable *item, bool wore) {
    float i = 1.f;
    // boolean to modify the behaviour if the item is being worn or being put off
    if (!wore)
        i = -1.f;

    // modify stats
    strength += i * item->getStrength();
    speed += i * item->getSpeed();
    hp += i * item->getHp();
    armor += i * item->getArmor();
}
