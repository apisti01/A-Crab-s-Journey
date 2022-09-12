//
// Created by longo on 07/07/2022.
//

#include "Room.h"
#include "FloorMap.h"
#include "Enemy_source_files/EnemyFactory.h"

Room::Room(std::string mapType, sf::Vector2i pos, sf::Vector2i dimensions) : mapType(mapType), pos(pos), dimensions(dimensions) {
    // doors are all initially closed
    doors = {-1, -1, -1, -1};

    grid = sf::Vector2i{int(round(dimensions.x / Game::getInstance()->getUnit())), int(round(dimensions.y / Game::getInstance()->getUnit()))};
};

void Room::generateWalls() {
    // walls
    if (grid.x % 2 == 0) {
        for (int i = 0; i < grid.x; i++) {
            if (i != grid.x / 2 - 1 && i != grid.x / 2) {
                walls.emplace_back(*new Collider({(i + .5f) / grid.x, .5f / grid.y}, {1.f, 1.f}));
                walls.emplace_back(*new Collider({(i + .5f) / grid.x, 1 - .5f / grid.y}, {1.f, 1.f}));
            }
        }
    } else {
        for (int i = 0; i < grid.x; i++) {
            if (i != floor(grid.x / 2) - 1 && i != floor(grid.x / 2) && floor(grid.x / 2) + 1) {
                walls.emplace_back(*new Collider({(i + .5f) / grid.x, .5f / grid.y}, {1.f, 1.f}));
                walls.emplace_back(*new Collider({(i + .5f) / grid.x, 1 - .5f / grid.y}, {1.f, 1.f}));
            }
        }

        walls.emplace_back(*new Collider({(floor(grid.x / 2.f) - .75f) / grid.x, .5f / grid.y}, {.5f, 1.f}));
        walls.emplace_back(*new Collider({(floor(grid.x / 2.f) + 1.75f) / grid.x, .5f / grid.y}, {.5f, 1.f}));
        walls.emplace_back(*new Collider({(floor(grid.x / 2.f) - .75f) / grid.x, 1 - .5f / grid.y}, {.5f, 1.f}));
        walls.emplace_back(*new Collider({(floor(grid.x / 2.f) + 1.75f) / grid.x, 1 - .5f / grid.y}, {.5f, 1.f}));
    }

    if (grid.y % 2 == 0) {
        for (int i = 1; i < grid.y - 1; i++) {
            if (i != grid.y / 2 - 1 && i != grid.y / 2) {
                walls.emplace_back(*new Collider({.5f / grid.x, (i + .5f) / grid.y}, {1.f, 1.f}));
                walls.emplace_back(*new Collider({1 - .5f / grid.x, (i + .5f) / grid.y}, {1.f, 1.f}));
            }
        }
    } else {
        for (int i = 1; i < grid.y - 1; i++) {
            if (i != floor(grid.y / 2) - 1 && i != floor(grid.y / 2) && i != floor(grid.y / 2) + 1) {
                walls.emplace_back(*new Collider({.5f / grid.x, (i + .5f) / grid.y}, {1.f, 1.f}));
                walls.emplace_back(*new Collider({1 - .5f / grid.x, (i + .5f) / grid.y}, {1.f, 1.f}));
            }
        }

        walls.emplace_back(*new Collider({.5f / grid.x, (floor(grid.y / 2.f) - .75f) / grid.y}, {1.f, .5f}));
        walls.emplace_back(*new Collider({.5f / grid.x, (floor(grid.y / 2.f) + 1.75f) / grid.y}, {1.f, .5f}));
        walls.emplace_back(*new Collider({1 - .5f / grid.x, (floor(grid.y / 2.f) - .75f) / grid.y}, {1.f, .5f}));
        walls.emplace_back(*new Collider({1 - .5f / grid.x, (floor(grid.y / 2.f) + 1.75f) / grid.y}, {1.f, .5f}));
    }
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

        // prepare collider and texture
        Collider collider(pickFreeGridSpot(), {1.f, 1.f});
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");

        // add the obstacle just created to the list
        obstacleList.emplace_back(obstacleTexture, collider);
    }
}

void Room::setupGrid() {
    // all cells start with false
    for (int i = 1; i < grid.x - 1; i++) {
        roomGrid.push_back({});
        for (int j = 1; j < grid.y - 1; j++) {
            roomGrid[i - 1].push_back(false);
        }
    }

    // obstacles can't be in front of open doors:
    // upper door
    if (doors[0] != -1) {
        if (grid.x % 2 == 0) {
            for (int i = (grid.x - 2) / 2 - 2; i < (grid.x - 2) / 2 + 2; i++) {
                for (int j = 0; j <= 1; j++)
                    roomGrid[i][j] = true;
            }
        } else {
            for (int i = floor((grid.x - 2) / 2) - 1; i <= floor((grid.x - 2) / 2) + 1; i++) {
                for (int j = 0; j <= 1; j++)
                    roomGrid[i][j] = true;
            }
        }
    }

    // right door
    if (doors[1] != -1) {
        if (grid.y % 2 == 0) {
            for (int i = grid.x - 4; i <= grid.x - 3; i++) {
                for (int j = (grid.y - 2) / 2 - 2; j < (grid.y - 2) / 2 + 2; j++)
                    roomGrid[i][j] = true;
            }
        } else {
            for (int i = grid.x - 4; i <= grid.x - 3; i++) {
                for (int j = floor((grid.y - 2) / 2) - 1; j <= floor((grid.y - 2) / 2) + 1; j++)
                    roomGrid[i][j] = true;
            }
        }
    }

    // bottom door
    if (doors[2] != -1) {
        if (grid.x % 2 == 0) {
            for (int i = (grid.x - 2) / 2 - 2; i < (grid.x - 2) / 2 + 2; i++) {
                for (int j = grid.y - 4; j <= grid.y - 3; j++) {
                    roomGrid[i][j] = true;
                }
            }
        } else {
            for (int i = floor((grid.x - 2) / 2) - 1; i <= floor((grid.x - 2) / 2) + 1; i++) {
                for (int j = grid.y - 4; j <= grid.y - 3; j++) {
                    roomGrid[i][j] = true;
                }
            }
        }
    }

    // left door
    if (doors[3] != -1) {
        if (grid.y % 2 == 0) {
            for (int i = 0; i <= 1; i++) {
                for (int j = (grid.y - 2) / 2 - 2; j < (grid.y - 2) / 2 + 2; j++)
                    roomGrid[i][j] = true;
            }
        } else {
            for (int i = 0; i <= 1; i++) {
                for (int j = floor((grid.y - 2) / 2) - 1; j <= floor((grid.y - 2) / 2) + 1; j++)
                    roomGrid[i][j] = true;
            }
        }
    }

    // if the room is the start one
    if (isStartRoom) {
        int startX, endX, startY, endY;
        if (grid.x % 2 == 0) {
            startX = (grid.x - 2) / 2 - 1;
            endX = (grid.x - 2) / 2 + 1;
        } else {
            startX = floor((grid.x - 2) / 2) - 1;
            endX = floor((grid.x - 2) / 2) + 2;
        }

        if (grid.y % 2 == 0) {
            startY = (grid.y - 2) / 2 - 1;
            endY = (grid.y - 2) / 2 + 1;
        } else {
            startY = floor((grid.y - 2) / 2) - 1;
            endY = floor((grid.y - 2) / 2) + 2;
        }

        // obstacles can't be in the center
        for (int i = startX; i < endX; i++) {
            for (int j = startY; j < endY; j++)
                roomGrid[i][j] = true;
        }
    }
}

sf::Vector2f Room::pickFreeGridSpot() {
    int posx = rand() % (grid.x - 2);
    int posy = rand() % (grid.y - 2);

    if (!roomGrid[posx][posy]) {
        roomGrid[posx][posy] = true;
        return sf::Vector2f{(1.5f + posx) / grid.x, (1.5f + posy) / grid.y};
    } else {
        return pickFreeGridSpot();
    }
}

void Room::loadDoors() {
    sf::Texture obstacleTexture;

    // TODO: random generation have to use a list of data
    std::string obstacleTypes[] = {"algae 1", "algae 2", "bottle 1", "bottle 2", "flipflop", "rock 1", "rock 2"};

    if (doors[0] == -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({.5f, .5f / grid.y}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
    if (doors[1] == -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({1.f - .5f / grid.x, .5f}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
    if (doors[2] == -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({.5f, 1 - .5f / grid.y}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
    if (doors[3] == -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({.5f / grid.x, .5f}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
}

void Room::generateEnemies(std::string mapType, int level) {
    enemyList = EnemyFactory::fillRoomWithEnemies(this, mapType, level);
}

void Room::updateEnemies(int deltaTime, FloorMap *floor, sf::RenderWindow &window) {
    // update enemy in the room
    for (auto &enemy : enemyList)
        enemy->update(deltaTime, floor, true, window);

    // check life of the enemies, if <= 0 erase them from the list
    auto enemy = enemyList.begin();
    while (enemy != enemyList.end()) {
        // if an enemy has less than 0 health points, delete it
        if ((*enemy)->getHp() > 0) {
            // next enemy
            ++enemy;
        } else {
            // update the bestiary and delete the enemy form the list
            floor->notifyObserver(enemy->get());
            enemy = enemyList.erase(enemy);
        }
    }
}

void Room::updateBullets(int deltaTime, FloorMap *floor) {
    // update every bullet in the room
    auto bullet = bulletList.begin();
    while (bullet != bulletList.end()) {
        bullet->update(deltaTime);

        // if a bullet hit something, delete it
        if (bullet->checkCollisions(floor)) {
            bullet = bulletList.erase(bullet);
        } else
            ++bullet;
    }
}

void Room::closeDoors() {
    sf::Texture obstacleTexture;
    std::string obstacleTypes[] = {"algae 1", "algae 2", "bottle 1", "bottle 2", "flipflop", "rock 1", "rock 2"};

    // for every door: if it's open, create an obstacle and put it there to close it
    if (doors[0] != -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({.5f, .5f / grid.y}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
    if (doors[1] != -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({1.f - .5f / grid.x, .5f}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
    if (doors[2] != -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({.5f, 1 - .5f / grid.y}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
    if (doors[3] != -1) {
        obstacleTexture.loadFromFile("Assets/Obstacle/" + obstacleTypes[rand() % size(obstacleTypes)] + ".png");
        Collider collider({.5f / grid.x, .5f}, {1.f, 1.f});
        obstacleList.emplace_back(obstacleTexture, collider);
    }
}

void Room::openDoors() {
    int roomToOpen = 0;
    for (int i = 0; i < size(doors); i++) {
        if (doors[i] != -1)
            roomToOpen++;
    }

    for (int i = 0; i < roomToOpen; i++)
        obstacleList.pop_back();
}

void Room::draw(sf::RenderWindow &window) {
    // draw background
    background.draw(window);

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
    for (auto bullet = bulletList.begin(); bullet != bulletList.end(); bullet++)
        bullet->draw(window);
}
