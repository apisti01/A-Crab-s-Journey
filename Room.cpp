//
// Created by longo on 07/07/2022.
//

#include <iostream>

#include "Room.h"
#include "Obstacle.h"

Room::Room(int posX, int posY, int width, int height) : posX(posX), posY(posY), width(width), height(height), XpReward(XpReward = 0),
isCage(isCage = false), isStartRoom(isStartRoom = false), isBossRoom(isBossRoom = false), isShopRoom(isShopRoom = false),
wallDepth(wallDepth = 0) {
    // doors are all initially closed
    doors = {-1, -1, -1, -1};

    // initialize all room grid cells to false
    setupGrid();

    // TODO: if it isn't the start room, create list of enemies
    if (!getStartRoom()) {

    }
};

void Room::setupGrid() {
    // all cells start with false
    for (int i = 0; i < size(roomGrid); i++) {
        for (int j = 0; j < size(roomGrid[i]); j++) {
            roomGrid[i][j] = false;
        }
    }

    // obstacles can't be in front of doors:
    // left and right door
    for (int i = 0; i <= 1; i++) {
        for (int j = 2; j <= 4; j++) {
            roomGrid[i][j] = true;
            roomGrid[size(roomGrid) - 1 - i][j] = true;
        }
    }
    // up and bottom door
    for (int i = 5; i <= 8; i++) {
        for (int j = 0; j <= 1; j++) {
            roomGrid[i][j] = true;
            roomGrid[i][size(roomGrid[i]) - 1 - j] = true;
        }
    }
}

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
    // in every room could appear from 1 to 4 obstacles
    int numObstacles = rand() % 4 + 1;

    sf::Texture obstacleTexture;

    // TODO: implementare l'utilizzo di una lista di oggetti per la generazione randomica
    std::string obstacleTypes[] = {"rock", "algae", "flipflop", "bottle"};

    // for every obstacle
    for (int i = 0; i < numObstacles; i++) {
        // get one free spot on room grid coordinates
        sf::Vector2i pos = pickFreeGridSpot();

        // prepare collider and texture
        Collider collider(pos.x, pos.y, 120, 120);
        obstacleTexture.loadFromFile("../Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");

        // add the obstacle just created to the list
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, pos.x, pos.y, 120, 120));
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
    std::string obstacleTypes[] = {"rock", "algae", "flipflop", "bottle"};

    if (doors[0] == -1) {
        obstacleTexture.loadFromFile("../Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(120 * 8, 60, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, 120 * 8, 60, 120, 120));
    }
    if (doors[1] == -1) {
        obstacleTexture.loadFromFile("../Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(width - 60, 120 * 4.5, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, width - 60, 120 * 4.5, 120, 120));
    }
    if (doors[2] == -1) {
        obstacleTexture.loadFromFile("../Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(120 * 8, height - 60, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, 120 * 8, height - 60, 120, 120));
    }
    if (doors[3] == -1) {
        obstacleTexture.loadFromFile("../Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider(60, 120 * 4.5, 120, 120);
        obstacleList.push_back(*new Obstacle(obstacleTexture, collider, 60, 120 * 4.5, 120, 120));
    }
}

/*
void Room::enterCageMode(Player &player) {
    // if player enter the room and there are enemies
    if (player.getPosX() > wallDepth && player.getPosX() < roomWidth - wallDepth && player.getPosY() > wallDepth && player.getPosY() < roomHeight - wallDepth && size(enemyList) != 0) {
        isCage = true;
    }
}

void Room::exitCageMode() {
    // when the player kills an enemy, if it's the last in the room
    if (size(enemyList) != 0) {
        isCage = false;
    }
}
*/

void Room::draw(sf::RenderWindow &window) {
    // draw walls
    for (int i = 0; i < size(walls); i++) {
        walls[i].draw(window);
    }

    // draw the obstacles in the room
    for (int i = 0; i < size(obstacleList); i++) {
        obstacleList[i].draw(window);
    }
}