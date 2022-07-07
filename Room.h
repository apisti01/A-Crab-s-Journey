//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_ROOM_H
#define ACRABSJOURNEY_ROOM_H

#include <array>

class Room {
public:

protected:
    int[] doors;
    int posX, posY;
    bool isCage;
    int enemyCount;
    std::array<Obstacle> obstacleList;
    std::array<Enemy> enemyList;
    bool isBossRoom;
    int XpReward;

private:
};

#endif //ACRABSJOURNEY_ROOM_H
