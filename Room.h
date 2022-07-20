//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_ROOM_H
#define ACRABSJOURNEY_ROOM_H

#include <vector>

#include "Obstacle.h"
#include "Enemy.h"

class Player;

class Room {
public:
    // constructor and destructor
    explicit Room(int posX, int posY, int width, int height);
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

    int getWidth() const {
        return width;
    }
    void setWidth(int width) {
        Room::width = width;
    }

    int getHeight() const {
        return height;
    }
    void setHeight(int height) {
        Room::height = height;
    }

    void draw(sf::RenderWindow &window);

    // obstacle and enemy lists
    std::vector<Obstacle> obstacleList;

protected:

private:
    // grid position attributes
    int posX, posY;

    // room measures
    int width, height;
    int wallDepth;

    void generateObstacles();

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
