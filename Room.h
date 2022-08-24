//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_ROOM_H
#define ACRABSJOURNEY_ROOM_H

#include <vector>

#include "Obstacle.h"
#include "Enemy_source_files/Enemy.h"
#include "Bullet.h"


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
    explicit Room(int posX, int posY, int width, int height, MapType mapType);
    ~Room() = default;
    Room(const Room& room) = delete;
    Room& operator = (const Room & room) = delete;

    // doors list: -1 for closed, n if connected to nth room
    std::vector<int> doors;

    // getter and setter for position attributes
    int getPosX() const { return posX; }
    void setPosX(int posx) { posX = posx; }

    int getPosY() const { return posY; }
    void setPosY(int posy) { posY = posy;}

    // getter and setter for special room's attributes
    bool getCage() const { return isCage; }
    void setCage(bool isCage) { Room::isCage = isCage; }

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

    int getWidth() const { return width; }
    void setWidth(int width) { Room::width = width; }

    int getHeight() const { return height; }
    void setHeight(int height) { Room::height = height; }

    void update(int deltaTime, FloorMap *floor);

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

    void generateEnemies(MapType mapType, int level);

    void closeDoors();

    sf::Vector2i pickFreeGridSpot();

private:
    // grid position attributes
    int posX{}, posY{};

    // texture and sprite
    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect{ 0, 0, 1920, 1080 } };

    // room measures
    int width{}, height{};
    int wallDepth {0};
    bool roomGrid[14][7]{};

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
