//
// Created by longo on 07/07/2022.
//

#include "FloorMap.h"
#include "Game.h"

FloorMap::FloorMap(int characterIndex, const std::string& mapType, int level, Bestiary &bestiary) :
                    mapType(mapType), level(level), roomWidth(1920), roomHeight(1080) {
    // there's a 40% chance that this floor has a shop room
    float chance = rand() / (RAND_MAX + 1.0);
    if (chance <= shopChance)
        hasShop = true;

    // then generates the floor
    generateFloor(mapType, bestiary);

    // subscribe to the observers
    subscribeObserver(&(Game::getInstance()->bestiary));

    // create and setup player
    setupPlayer(characterIndex);
}

FloorMap::~FloorMap() {
    // unsubscribe observers
    unsubscribeObserver(&(Game::getInstance()->bestiary));
}

void FloorMap::generateFloor(std::string mapType, Bestiary &bestiary) {
    // add first room in the middle of the grid (position 0, 0)
    roomList.push_back(std::make_unique<Room>(mapType, 0, 0, roomWidth, roomHeight));

    // calculate number of rooms in the floor
    numRooms = round(10 - exp(1.8 - level / 4));

    // for every room to add
    for (int i = 1; i < numRooms; i++) {
        // pick a room with at least one free side
        int roomIndex = FloorMap::pickRoom();
        // of that room, pick a free side
        int sideIndex = FloorMap::pickFreeSide(roomIndex);
        // generate a new room
        generateRoom(roomIndex, sideIndex, i);
    }

    // set start and end rooms
    setStartAndEndRooms();

    // then add room's door colliders
    for (int i = 0; i < size(roomList); i++) {
        // add walls to the room
        roomList[i]->generateWalls();

        // if the room is not the boss room, generate obstacles
        if (!roomList[i]->getBossRoom())
            roomList[i]->generateObstacles();

        // if the room is not the start room, generate enemies
        if (!roomList[i]->getStartRoom())
            roomList[i]->generateEnemies(&bestiary, mapType, level);

        // close the doors that don't connect with other rooms
        roomList[i]->closeDoors();
    }

    // set the shop room
    setShopRoom();
};

int FloorMap::pickRoom() {
    bool availableRoomFounded = false;
    int roomIndex;
    bool isSurrounded;
    while (!availableRoomFounded) {
        // generate a random  number between 0 and the number of rooms
        roomIndex = rand() % size(roomList);

        // check if the room picked is not surrounded by other rooms
        isSurrounded = true;
        // for every side of the room
        int otherSideX, otherSideY;
        for (int i = 0; i < 4; i++) {
            // calculate coordinates for the adjacent grid cell
            otherSideX = roomList[roomIndex]->getPosX() + round(sin(i * M_PI / 2));
            otherSideY = roomList[roomIndex]->getPosY() - round(cos(i * M_PI / 2));

            bool isOccupied = false;
            // check for a room in the cell: for every room
            for (int j = 0; j < size(roomList); j++) {
                // if the room coordinates are the same as the cell coordinates
                if (roomList[j]->getPosX() == otherSideX && roomList[j]->getPosY() == otherSideY) {
                    // the cell is occupied
                    isOccupied = true;
                }
            }

            // if the cell is not occupied
            if (!isOccupied) {
                // the room is not surrounded, hence has at least one free side
                isSurrounded = false;
            }
        }

        // if the room is not surrounded
        if (!isSurrounded)
            // an available room is founded
            availableRoomFounded = true;
    }

    // return the index of the available room
    return roomIndex;
}

int FloorMap::pickFreeSide(int roomIndex) {
    // create a list of all room's free side indexes
    std::vector<int> freeSideIndexList;

    // for every adjacent cell
    int otherSideX, otherSideY;
    for (int i = 0; i < 4; i++) {
        // calculate coordinates for the adjacent grid cell
        otherSideX = roomList[roomIndex]->getPosX() + round(sin(i * M_PI / 2));
        otherSideY = roomList[roomIndex]->getPosY() - round(cos(i * M_PI / 2));

        bool isOccupied = false;
        // for every room
        for (int j = 0; j < size(roomList); j++) {
            // if the room coordinates are the same as the cell coordinates
            if (roomList[j]->getPosX() == otherSideX && roomList[j]->getPosY() == otherSideY) {
                // the cell is occupied
                isOccupied = true;
            }
        }

        // if the cell is not occupied
        if (!isOccupied) {
            // add free side index to side list
            freeSideIndexList.push_back(i);
        }
    }

    // generate a random number from 0 to length of free sides
    int freeSide = rand() % size(freeSideIndexList);

    // return a random side
    return freeSideIndexList[freeSide];
}

void FloorMap::generateRoom(int roomIndex, int sideIndex, int newRoomIndex) {
    // calculate new room's grid coordinates
    int otherSideX = roomList[roomIndex]->getPosX() + round(sin(sideIndex * M_PI / 2));
    int otherSideY = roomList[roomIndex]->getPosY() - round(cos(sideIndex * M_PI / 2));

    // check for min and max value on the axis
    if (otherSideX < minX)
        minX = otherSideX;
    else if (otherSideX > maxX)
        maxX = otherSideX;
    if (otherSideY < minY)
        minY = otherSideY;
    else if (otherSideY > maxY)
        maxY = otherSideY;

    roomList.push_back(std::make_unique<Room>(mapType, otherSideX, otherSideY, roomWidth, roomHeight));

    // assign adjacent room index to start and new room
    roomList[roomIndex]->doors[sideIndex] = newRoomIndex;
    roomList[newRoomIndex]->doors[(sideIndex + 2) % 4] = roomIndex;
}

void FloorMap::setStartAndEndRooms() {
    // select one random room from all terminal rooms
    endRoomIndex = TerminalRoomIndex();

    int oldPathLength = -1;
    int newPathLength = 0;

    // while back and forth paths gives different length
    while (oldPathLength != newPathLength) {
        oldPathLength = newPathLength;
        startRoomIndex = endRoomIndex;

        // reset path length
        setLongestPathLength(0);
        // from start room, visit recursively all adjacent rooms
        visitAdjacentRooms(startRoomIndex);
        // calculate new path length
        newPathLength = getLongestPathLength();
    }

    roomList[startRoomIndex]->setStartRoom(true);
    roomList[endRoomIndex]->setBossRoom(true);

    // set the start room to be the current room
    currentRoomIndex = startRoomIndex;
}

int FloorMap::TerminalRoomIndex() {
    // list of all terminal rooms
    std::vector<int> terminalRoomIndexes;

    // counter
    int numAdjacentRooms;
    // for every room
    for (int i = 0; i < numRooms; i++) {
        // count number of connections
        numAdjacentRooms = 0;

        // for every side
        for (int j = 0; j < 4; j++) {
            // if there's a connection
            if (roomList[i]->doors[j] != -1) {
                // increment counter
                numAdjacentRooms++;
            }
        }

        // if room has only one connection
        if (numAdjacentRooms == 1) {
            // is a terminal room
            terminalRoomIndexes.emplace_back(i);
        }
    }

    // return one random index room from the list of all terminal rooms
    int index = rand() % size(terminalRoomIndexes);
    return terminalRoomIndexes[index];
}

int FloorMap::visitAdjacentRooms(int index, int prev, int dist) {
    bool isTerminalRoom = true;

    // for every side
    for (int i = 0; i < 4; i++) {
        // if there's a connection with another room, except for the previous
        if (roomList[index]->doors[i] != -1 && i != prev) {
            // the room is not terminal
            isTerminalRoom = false;

            // visit that room
            visitAdjacentRooms(roomList[index]->doors[i], (i + 2) % 4, dist + 1);
        }
    }

    // if the room is terminal and the path founded is longer than the previous one
    if (isTerminalRoom && dist >= getLongestPathLength()) {
        // this room become the end room
        endRoomIndex = index;

        // and new longest path is set
        setLongestPathLength(dist);
    }
    return 0;
}

void FloorMap::setShopRoom() {
    // there's a chance of 40% that the floor has a shop room
    if (rand() / (RAND_MAX + 1.0) <= shopChance) {
        // create a list of all possible
        std::vector<int> possibleShopRoomIndexes;

        // select one random room except for start and boss room
        for (int i = 0; i < size(roomList); i++) {
            // shop room can't be the same as the boss room
            if (i != endRoomIndex)
                possibleShopRoomIndexes.emplace_back(i);
        }

        // select one random room from all the possible rooms
        shopRoomIndex = possibleShopRoomIndexes[rand() % size(possibleShopRoomIndexes)];
        // and set its attribute true
        roomList[shopRoomIndex]->setShopRoom(true);
    }
}

void FloorMap::setupPlayer(int characterIndex) {
    auto character = Game::getInstance()->globalProgress.characters[characterIndex];
    // load brown crab's texture for movement animation
    sf::Texture characterTexture;
    characterTexture.loadFromFile("GameCharacter/Player/" + character.name + "/Animations/Texture.png");

    // Ranged weapon
    std::unique_ptr<Weapon> rangedWeapon = std::make_unique<RangedWeapon>(RangedWeaponType::Rock);
    // give him a melee weapon
    // std::unique_ptr<Weapon> weapon = std::make_unique<MeleeWeapon>(10, "player", ItemRarity::Common, 50);

    // and a collider
    Collider collider(float(roomWidth) / 2, float(roomHeight) / 2,
                      characterTexture.getSize().x / 6 * 0.4 * 0.6,
                      characterTexture.getSize().y / 3 * 0.4 * 0.8);

    CrabSpecie characterSpecie;
    if (character.name == "BrownCrab")
        characterSpecie = CrabSpecie::BrownCrab;
    else if (character.name == "FiddlerCrab")
        characterSpecie = CrabSpecie::FiddlerCrab;
    else if (character.name == "TriangleTannerCrab")
        characterSpecie = CrabSpecie::TriangleTannerCrab;
    else if (character.name == "AsianGreatPaddle")
        characterSpecie = CrabSpecie::AsianGreatPaddle;

    // create the player
    player = make_unique<Player>(characterIndex, "Crab", characterSpecie, std::move(characterTexture), collider,
                                 std::move(rangedWeapon), character.health, character.health, character.speed,
                                 character.speed, character.armor, character.armor, character.strength,
                                 character.strength);

    // and set his position at the center of the map
    player->setPosition(roomWidth / 2, roomHeight / 2);
}

// tells if player is near the shop
bool FloorMap::isPlayerNearShop() {
    // shop position in the room
    sf::Vector2f shopPos {float(roomWidth), 0};

    // if player is in the shop room and it's near the shop corner
    if (currentRoomIndex == shopRoomIndex && sqrtf(powf(player->getPosX() - shopPos.x, 2) + powf(player->getPosY() - shopPos.y, 2)) < 600)
        return true;
    else
        return false;
}

bool FloorMap::floorCompleted() {
    // if player is in the boss room and it's empty
    if (currentRoomIndex == endRoomIndex && !roomList[currentRoomIndex]->getCage())
        return true;
    else
        return false;
}

void FloorMap::update(int deltaTime, bool attack) {
    // update the current room
    if (roomList[currentRoomIndex]->getCage())
        roomList[currentRoomIndex]->updateEnemies(deltaTime, this);
    roomList[currentRoomIndex]->updateBullets(deltaTime, this);

    // and the player: check if it's still alive
    player->update(deltaTime, this, attack);
    // if not change state to main menu
    if (player->getHp() <= 0) {
        // TODO: it has to be the Game Over State
        Game::getInstance()->changeState(StateType::MainMenu);
    }
}


void FloorMap::draw(sf::RenderWindow &window) {
    roomList[currentRoomIndex]->draw(window);
    player->draw(window);
}

void FloorMap::subscribeObserver(Observer *obs) { observers.push_back(obs); }

void FloorMap::unsubscribeObserver(Observer *obs) { observers.remove(obs); }

void FloorMap::notifyObserver(Room *room) {
    for (auto obs : observers)
        obs->update(room);
}

void FloorMap::notifyObserver(Enemy *enemy) {
    for (auto obs : observers)
        obs->update(enemy);
}