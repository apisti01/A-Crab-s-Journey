//
// Created by longo on 07/07/2022.
//
#include <iostream>

#include "Room.h"
#include "GameCharacter.h"


Room::Room(int posX, int posY, int width, int height, MapType mapType) : posX(posX), posY(posY), width(width),
height(height), XpReward(XpReward = 0), isCage(isCage = false), isVisited(false), isStartRoom(isStartRoom = false),
isBossRoom(isBossRoom = false), isShopRoom(isShopRoom = false), wallDepth(wallDepth = 0) {
    // doors are all initially closed
    doors = {-1, -1, -1, -1};

    // load coral reef texture as room background
    switch (mapType) {
        case MapType::CoralReef:
            backgroundTexture.loadFromFile("Map/Coral Reef/Coral Reef.png");
            break;
        case MapType::MangroveForest:
            backgroundTexture.loadFromFile("Map/Mangrove Forest/Mangrove Forest.png");
            break;
        case MapType::TemperateReef:
            backgroundTexture.loadFromFile("Map/Temperate Reef/Temperate Reef.png");
            break;
        case MapType::KelpForest:
            backgroundTexture.loadFromFile("Map/Kelp Forest/Kelp Forest.png");
            break;
        case MapType::PosidoniaMeadow:
            backgroundTexture.loadFromFile("Map/Posidonia Meadow/Posidonia Meadow.png");
            break;
        case MapType::IceFloe:
            backgroundTexture.loadFromFile("Map/Ice Floe/Ice Floe.png");
            break;
    }

    // TODO: if it isn't the start room, create list of enemies
    if (!getStartRoom()) {

    }
};

void Room::generateWalls() {
    // walls
    for (int i = 0; i < 16; i++) {
        if (i != 7 && i != 8) {
            walls.emplace_back(*new Collider(i * 120 + 60, 60, 120, 120));
            walls.emplace_back(*new Collider(i * 120 + 60, height - 60, 120, 120));
        }
    }
    for (int i = 1; i < 8; i++) {
        if (i != 3 && i != 4 && i != 5) {
            walls.emplace_back(*new Collider(60, i * 120 + 60, 120, 120));
            walls.emplace_back(*new Collider(width - 60, i * 120 + 60, 120, 120));
        }
    }
    walls.emplace_back(*new Collider(60, 3.25 * 120, 120, 60));
    walls.emplace_back(*new Collider(width - 60, 3.25 * 120, 120, 60));
    walls.emplace_back(*new Collider(60, 5.75 * 120, 120, 60));
    walls.emplace_back(*new Collider(width - 60, 5.75 * 120, 120, 60));
}

void Room::generateObstacles() {
    // initialize all room grid cells to false
    setupGrid();

    // in every room could appear from 1 to 4 obstacles
    int numObstacles = rand() % 4 + 1;

    sf::Texture obstacleTexture;

    std::string obstacleTypes[] = {"algae 1", "algae 2", "bottle 1", "bottle 2", "flipflop", "rock 1", "rock 2"} ;

    // for every obstacle
    for (int i = 0; i < numObstacles; i++) {
        // get one free spot on room grid coordinates
        sf::Vector2i pos = pickFreeGridSpot();

        // prepare collider and texture
        Collider collider(pos.x, pos.y, 120, 120);
        obstacleTexture.loadFromFile("Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");

        // add the obstacle just created to the list
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, pos.x, pos.y, 120, 120));
    }
}

void Room::setupGrid() {
    // all cells start with false
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 7; j++) {
            roomGrid[i][j] = false;
        }
    }

    // obstacles can't be in front of open doors:
    // upper door
    if (doors[0] != -1) {
        for (int i = 5; i <= 8; i++) {
            for (int j = 0; j <= 1; j++) {
                roomGrid[i][j] = true;
            }
        }
    }
    // right door
    if (doors[1] != -1) {
        for (int i = 12; i <= 13; i++) {
            for (int j = 2; j <= 4; j++)
                roomGrid[i][j] = true;
        }
    }
    // bottom door
    if (doors[2] != -1) {
        for (int i = 5; i <= 8; i++) {
            for (int j = 5; j <= 6; j++) {
                roomGrid[i][j] = true;
            }
        }
    }
    // left door
    if (doors[3] != -1) {
        for (int i = 0; i <= 1; i++) {
            for (int j = 2; j <= 4; j++)
                roomGrid[i][j] = true;
        }
    }

    // if the room is the start one
    if (isStartRoom) {
        // obstacles can't be in the center
        for (int i = 6; i <= 7; i++) {
            for (int j = 2; j <= 4; j++)
                roomGrid[i][j] = true;
        }
    }
}

sf::Vector2i Room::pickFreeGridSpot() {
    int posx = rand() % 14;
    int posy = rand() % 7;

    if (!roomGrid[posx][posy]) {
        roomGrid[posx][posy] = true;
        return sf::Vector2i { (posx + 1) * 120 + 60, (posy + 1) * 120 + 60};
    } else {
        return pickFreeGridSpot();
    }
}

void Room::closeDoors() {
    sf::Texture obstacleTexture;

    // TODO: implementare l'utilizzo di una lista di oggetti per la generazione randomica
    std::string obstacleTypes[] = {"algae 1", "algae 2", "bottle 1", "bottle 2", "flipflop", "rock 1", "rock 2"} ;

    if (doors[0] == -1) {
        obstacleTexture.loadFromFile("Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(120 * 8, 60, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, 120 * 8, 60, 120, 120));
    }
    if (doors[1] == -1) {
        obstacleTexture.loadFromFile("Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(width - 60, 120 * 4.5, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, width - 60, 120 * 4.5, 120, 120));
    }
    if (doors[2] == -1) {
        obstacleTexture.loadFromFile("Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(120 * 8, height - 60, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, 120 * 8, height - 60, 120, 120));
    }
    if (doors[3] == -1) {
        obstacleTexture.loadFromFile("Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(60, 120 * 4.5, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, 60, 120 * 4.5, 120, 120));
    }
}

void Room::update(int deltaTime, FloorMap *floor) {
    //update enemy in the room
    for (auto &enemy : enemyList)
        enemy->update(deltaTime, floor, true);

    // move every bullet in the room
    for (auto bullet = bulletList.begin(); bullet != bulletList.end() ; bullet++) {
        bullet->move(deltaTime);
    } // TODO check collisions of the bullets, deal damage and destroy them
}

void Room::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    // draw walls
    for (int i = 0; i < size(walls); i++)
        walls[i].draw(window);

    // draw the obstacles in the room
    for (int i = 0; i < size(obstacleList); i++)
        obstacleList[i].draw(window);

    // draw every enemy still alive
    for (auto &enemy : enemyList)
        enemy->draw(window);

    // draw every bullet in the room
    for (auto bullet = bulletList.begin(); bullet != bulletList.end() ; bullet++)
        bullet->draw(window);
}

