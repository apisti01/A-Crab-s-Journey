//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_ROOM_H
#define ACRABSJOURNEY_ROOM_H

#include "Obstacle.h"

class Room {
public:
    // constructor and destructor
    explicit Room(int posX, int posY);
    // ~Room();

    // getter and setter for position attributes
    int getPosX() const {
        return posX;
    }
    void setPosX(int posx) {
        posX = posx;
    }

    int getPosY() const {
        return posY;
    }
    void setPosY(int posy) {
        posY = posy;
    }

    std::vector<int> doors;

protected:
    bool isCage;
    int enemyCount;
    std::vector<Obstacle> obstacleList;
    // std::vector<Enemy> enemyList;
    bool isBossRoom;
    int XpReward;

private:
    int posX, posY;
};

#endif //ACRABSJOURNEY_ROOM_H
