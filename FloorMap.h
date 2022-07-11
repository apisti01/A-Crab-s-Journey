//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_FLOORMAP_H
#define ACRABSJOURNEY_FLOORMAP_H

#include "Room.cpp"
using namespace std;

class FloorMap {
public:
    // constructor
    explicit FloorMap(int level) : level(level) {
        generateFloor();
    };

    // getter and setter for level attribute
    int getLevel() const {
        return level;
    }
    void setLevel(int level) {
        FloorMap::level = level;
    }

    // getter and setter for number of rooms
    int getNumRooms() const {
        return numRooms;
    }
    void setNumRooms(int numRooms) {
        FloorMap::numRooms = numRooms;
    }

    // getter and setter for number of rooms
    int getLongestPathLength() const {
        return longestPathLength;
    }
    void setLongestPathLength(int longestPathLength) {
        FloorMap::longestPathLength = longestPathLength;
    }

    // list of all rooms on floor
    std::vector<Room> roomList;
    int indexStartRoom, indexEndRoom;

protected:

private:
    // level and number of rooms
    int level;
    int numRooms;
    int longestPathLength;

    // start, end and current room index
    int indexCurrentRoom;

    // function for randomic floor generation
    void generateFloor();
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
};

class CoralReef : public FloorMap {

};

class MangroveForest : public FloorMap {

};

class PosidoniaMeadow : public FloorMap {

};

class TemperateReef : public FloorMap {

};

class KelpForest : public FloorMap {

};

class IceFloe : public FloorMap {

};


#endif //ACRABSJOURNEY_FLOORMAP_H