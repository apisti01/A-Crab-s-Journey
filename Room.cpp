//
// Created by longo on 07/07/2022.
//

#include "Room.h"
#include "Obstacle.h"

Room::Room(int posX, int posY, int width, int height) : posX(posX), posY(posY), width(width), height(height), XpReward(XpReward = 0),
isCage(isCage = false), isStartRoom(isStartRoom = false), isBossRoom(isBossRoom = false), isShopRoom(isShopRoom = false),
wallDepth(wallDepth = 0) {
    // doors are all initially closed
    doors = {-1, -1, -1, -1};

    // TODO: create list of obstacles
    generateObstacles();

    // TODO: if it isn't the start room, create list of enemies
    if (!getStartRoom()) {

    }
};

void Room::generateObstacles() {
    // in every room could appear from 1 to 4 obstacles
    int numObstacles = rand() % 4 + 1;

    // for every obstacle
    for (int i = 0; i < numObstacles; i++) {
        // TODO: choose one random obstacles

        // get random coordinates
        float posx = (rand() % 14 + 1) * 120;
        float posy = (rand() % 7 + 1) * 120;

        // prepare sprite
        sf::Texture rockTexture;
        rockTexture.loadFromFile("../Obstacle/rock.png");

        // prepare collider
        Collider collider(posx, posy, 120, 120);

        // add the obstacle just created to the list
        obstacleList.push_back(*new Obstacle(rockTexture, collider, posx, posy, 120, 120));
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
    // first draw background
    window.draw(background);

    // draw the obstacles in the room
    for (int i = 0; i < size(obstacleList); i++) {
        obstacleList[i].draw(window);
    }

    /*
    // draw all the enemies present
    for (auto & enemy : enemyList) {
        enemy->draw(window);
    }
     */
}