//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_FLOORMAP_H
#define ACRABSJOURNEY_FLOORMAP_H

#include <vector>

#include "Player.h"
#include "Room.h"

class Observer;

class FloorMap {
public:
    // constructor
    explicit FloorMap(int characterIndex, const std::string &mapType, int level);
    ~FloorMap();

    // getter and setter for level attribute
    int getLevel() const { return level; }
    void setLevel(int level) { FloorMap::level = level; }

    // getter and setter for number of rooms
    int getNumRooms() const { return numRooms; }
    void setNumRooms(int numRooms) { FloorMap::numRooms = numRooms; }

    // getter and setter for number of rooms
    int getLongestPathLength() const { return longestPathLength; }
    void setLongestPathLength(int longestPathLength) { FloorMap::longestPathLength = longestPathLength; }

    // list of all rooms on floor
    std::vector<std::unique_ptr<Room>> roomList {};
    int currentRoomIndex, startRoomIndex, endRoomIndex, shopRoomIndex = -1;

    std::unique_ptr<Player> player;

    void update(int deltaTime, bool attack);

    void draw(sf::RenderWindow &window);

    bool isPlayerNearShop();
    bool floorCompleted();

    // functions for the observers ( bestiary and achievements)
    void subscribeObserver(Observer *obs);
    void unsubscribeObserver(Observer *obs);

    // overloaded functions to notify observers
    void notifyObserver(Room *room);
    void notifyObserver(Enemy *enemy);

    std::string mapType;
    float minX = 0;
    float maxX = 0;
    float minY = 0;
    float maxY = 0;

private:
    // level and number of rooms
    int level, numRooms;

    int roomWidth, roomHeight;

    int longestPathLength;
    bool hasShop;
    float shopChance = 0.5;

    // function for randomic floor generation
    void generateFloor(std::string mapType);
    // returns the index of a room with at least one free side
    int pickRoom();
    // given a room index, returns the index of a free side
    int pickFreeSide(int roomIndex);
    // randomic generation of a room (enemies, obstacles ecc.)
    void generateRoom(int roomIndex, int sideIndex, int newRoomIndex);

    // finds two furthest rooms in the floor
    void setStartAndEndRooms();
    // returns the index of one random terminal room (rooms with only one connection)
    int TerminalRoomIndex();
    // given an index of a room, visits all adjacent rooms and return number of rooms in the longest path
    int visitAdjacentRooms(int index, int prev = -1, int dist = 1);

    // set shop room
    void setShopRoom();

    //  create the player and prepare it for the game
    void setupPlayer(int characterIndex);

    // list of the observers subscribed
    std::list<Observer*> observers {};
};

#endif //ACRABSJOURNEY_FLOORMAP_H
