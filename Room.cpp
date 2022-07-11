//
// Created by longo on 07/07/2022.
//

#include <vector>
#include "Room.h"
#include "Obstacle.h"

using namespace std;

Room::Room(int posX, int posY) : posX(posX), posY(posY), XpReward(XpReward = 0), isCage(isCage = false), enemyCount(enemyCount = 0), isBossRoom(isBossRoom = false) {
    // doors are all initially closed
    doors = {-1, -1, -1, -1};

    // TODO: create list of obstacles
    // obstacleList;

    // TODO: create list of enemies
    // enemyList;
};