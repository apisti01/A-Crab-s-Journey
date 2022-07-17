//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_ROOM_H
#define ACRABSJOURNEY_ROOM_H

#include <vector>

#include "Obstacle.h"
#include "Enemy.h"
#include "Player.h"

class Room {
public:
    // constructor and destructor
    explicit Room(int posX, int posY);
    // ~Room();

    // doors list:
    // - -1 for closed
    // - n if connected to nth room
    std::vector<int> doors;

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

    // getter and setter for special room's attributes
    bool getCage() const {
        return isCage;
    }
    void setCage(bool isCage) {
        Room::isCage = isCage;
    }

    bool getStartRoom() const {
        return isStartRoom;
    }
    void setStartRoom(bool isStartRoom) {
        Room::isStartRoom = isStartRoom;
    }

    bool getBossRoom() const {
        return isBossRoom;
    }
    void setBossRoom(bool isBossRoom) {
        Room::isBossRoom = isBossRoom;
    }

    bool getShopRoom() const {
        return isShopRoom;
    }
    void setShopRoom(bool isShopRoom) {
        Room::isShopRoom = isShopRoom;
    }

    int getXpReward() const {
        return XpReward;
    }
    void setXpReward(int xpReward) {
        XpReward = xpReward;
    }

protected:

private:
    // grid position attributes
    int posX, posY;

    // room measures
    int roomWidth, roomHeight;
    int wallDepth;

    // obstacle and enemy lists
    std::vector<Obstacle> obstacleList;
    // std::vector<std::unique_ptr<Enemy>> enemyList;

    // room state
    bool isCage;

    // special rooms
    bool isStartRoom;
    bool isBossRoom;
    bool isShopRoom;

    // xp rewarded when completed
    int XpReward;

    // change room status
    // void enterCageMode(Player &player);
    // void exitCageMode();
};

#endif //ACRABSJOURNEY_ROOM_H
