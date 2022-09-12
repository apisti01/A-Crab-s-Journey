//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_ROOM_H
#define ACRABSJOURNEY_ROOM_H

#include <vector>

#include "Obstacle.h"
#include "Enemy_source_files/Enemy.h"
#include "Bullet.h"
#include "Bestiary.h"
#include "SpriteButton.h"

enum class MapType {
    CoralReef,
    MangroveForest,
    TemperateReef,
    KelpForest,
    PosidoniaMeadow,
    IceFloe,
};

class Room {
public:
    // constructor and destructor
    explicit Room(std::string mapType, sf::Vector2i pos, sf::Vector2i dimensions);
    ~Room() = default;
    Room(const Room& room) = delete;
    Room& operator = (const Room & room) = delete;

    // doors list: -1 for closed, n if connected to nth room
    std::vector<int> doors;

    // getter and setter for position attributes
    sf::Vector2i getPos() const { return pos; }
    void setPos(sf::Vector2i pos) { Room::pos = pos; }
    int getPosX() const { return pos.x; }
    void setPosX(int posX) { pos.x = posX; }
    int getPosY() const { return pos.y; }
    void setPosY(int posY) { pos.y = posY;}

    sf::Vector2i getDimensions() const { return dimensions; }
    void setDimensions(sf::Vector2i dimensions) { Room::dimensions = dimensions; }
    int getWidth() const { return dimensions.x; }
    void setWidth(int width) { Room::dimensions.x = width; }
    int getHeight() const { return dimensions.y; }
    void setHeight(int height) { Room::dimensions.y = height; }


    // getter and setter for special room's attributes
    bool getCage() const { return isCage; }
    void setCage(bool isCage) {
        Room::isCage = isCage;
        if (isCage)
            closeDoors();
        else
            openDoors();
    }

    bool getVisited() const { return isVisited; }
    void setVisited(bool isVisited) { Room::isVisited = isVisited; }

    bool getStartRoom() const { return isStartRoom; }
    void setStartRoom(bool isStartRoom) { Room::isStartRoom = isStartRoom;}

    bool getBossRoom() const { return isBossRoom; }
    void setBossRoom(bool isBossRoom) { Room::isBossRoom = isBossRoom; }

    bool getShopRoom() const { return isShopRoom; }
    void setShopRoom(bool isShopRoom) { Room::isShopRoom = isShopRoom; }

    int getXpReward() const { return XpReward; }
    void setXpReward(int xpReward) { XpReward = xpReward; }

    void updateEnemies(int deltaTime, FloorMap *floor, sf::RenderWindow &window);
    void updateBullets(int deltaTime, FloorMap *floor);

    void draw(sf::RenderWindow &window);

    // obstacle and enemy lists
    std::vector<Obstacle> obstacleList {};

    // list of the enemy present in the room, when they die they are deleted
    std::list<std::unique_ptr<Enemy>> enemyList {};

    // list of all bullets in the room
    std::list<Bullet> bulletList{};

    // collider for the walls
    std::vector<Collider> walls {};

    void generateWalls();

    void generateObstacles();

    void generateEnemies(std::string mapType, int level);

    void loadDoors();

    void closeDoors();
    void openDoors();

    sf::Vector2f pickFreeGridSpot();

private:
    // grid position attributes
    sf::Vector2i pos;
    std::string mapType;

    // room measures
    sf::Vector2i dimensions;
    sf::Vector2i grid;

    // texture and sprite
    SpriteButton background = {"Assets/Map/" + mapType + "/Background Texture.png", 1, {.50f, .50f}};
    std::vector<std::vector<bool>> roomGrid;

    void setupGrid();

    // room state
    bool isCage {false};
    bool isVisited {false};

    // special rooms
    bool isStartRoom {false};
    bool isBossRoom {false};
    bool isShopRoom {false};

    // xp rewarded when completed
    int XpReward {0};
};

#endif //ACRABSJOURNEY_ROOM_H
