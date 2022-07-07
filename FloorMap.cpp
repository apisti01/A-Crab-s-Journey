//
// Created by longo on 07/07/2022.
//

#include "FloorMap.h"
#include "cstdlib"
#include "cmath"

using namespace std;

FloorMap::FloorMap() : level(level) {

};

void FloorMap::generateFloor(level) {
    // TODO: create first room with index 0

    // number of rooms in the floor
    int numRooms = level + 4;
    for (int i = 1; i <= numRooms; i++) {
        int roomIndex = FloorMap::pickRoom();
        int sideIndex = FloorMap::pickFreeSide(roomIndex);
        FloorMap::generateRoom(roomIndex, sideIndex, i);
    }
};

int FloorMap::pickRoom() {
    bool availableRoomFounded = false;
    while (availableRoomFounded == false) {
        // generate a random number between 0 and the number of rooms
        int roomIndex = rand() % length(roomList);

        // check if the room picked is not surrounded by other rooms
        bool isSurrounded = true;
        // for every side of the room
        for (int i = 0; i < 4; i++) {
            // calculate coordinates for the adjacent grid cell
            int otherSideX = roomList[roomIndex].posX + sin(i * M_PI / 2);
            int otherSideY = roomList[roomIndex].posY - cos(i * M_PI / 2);

            bool isOccupied = false;
            // check for a room in the cell: for every room
            for (int j = 0; j < length(roomList); j++) {
                // if the room coordinates are the same as the cell coordinates
                if (roomList[j].posX == otherSideX && roomList[j].posY == otherSideY) {
                    // the cell is occupied
                    isOccupied = true;
                }
            }

            // if the cell is not occupied
            if (isOccupied == false) {
                // the room is not surrounded, hence has at least one free side
                isSurrounded = false;
            }
        }

        // if the room is not surrounded
        if (isSurrounded == false)
            // an available room is founded
            availableRoomFounded = true;
    }

    // return the index of the available room
    return roomIndex;
}

int FloorMap::pickFreeSide(int roomIndex) {
    std::array<int> freeSidesList = [];
    // for every side of the room
    for (int i = 0; i < 4; i++) {
        // calculate coordinates for the adjacent grid cell
        int otherSideX = roomList[roomIndex].posX + sin(i * M_PI / 2);
        int otherSideY = roomList[roomIndex].posY - cos(i * M_PI / 2);

        bool isOccupied = false;
        // check for a room in the cell: for every room
        for (int j = 0; j < length(roomList); j++) {
            // if the room coordinates are the same as the cell coordinates
            if (roomList[j].posX == otherSideX && roomList[j].posY == otherSideY) {
                // the cell is occupied
                isOccupied = true;
            }
        }

        // if the cell is not occupied
        if (isOccupied == false) {
            // the room is not surrounded, hence has at least one free side
            isSurrounded = false;

            // add index to side list
            freeSideList.push(i);
        }
    }

    // generate a random number from 0 to length of free sides
    int sideIndex = rand() % length(freeSidesList);

    // return a random side
    return freeSideList[sideIndex];
}

void FloorMap::generateRoom(int roomIndex, int sideIndex, int newRoomIndex) {
    // TODO: generate new room with room constructor

    // assign adjacent room index to start and new room
    roomList[roomIndex].doors[sideIndex] = newRoomIndex;
    roomList[newRoomIndex].doors[(sideIndex + 2) % 4] = roomIndex;
}