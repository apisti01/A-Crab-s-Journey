//
// Created by longo on 07/07/2022.
//

#include "FloorMap.h"

using namespace std;

void FloorMap::generateFloor() {
    // add first room in the middle of the grid (position 0, 0)
    roomList.push_back(*new Room(0, 0));

    // calculate number of rooms in the floor
    numRooms = round(10 - exp(1.8 - level / 4));

    // for every room to add
    for (int i = 1; i < numRooms; i++) {
        // pick a room with at least one free side
        int roomIndex = FloorMap::pickRoom();
        // of that room, pick a free side
        int sideIndex = FloorMap::pickFreeSide(roomIndex);
        // generate a new room
        FloorMap::generateRoom(roomIndex, sideIndex, i);
    }

    // set start and end rooms
    setStartAndEndRooms();
};

int FloorMap::pickRoom() {
    bool availableRoomFounded = false;
    int roomIndex;
    bool isSurrounded;
    while (!availableRoomFounded) {
        // generate a random number between 0 and the number of rooms
        roomIndex = rand() % size(roomList);

        // check if the room picked is not surrounded by other rooms
        isSurrounded = true;
        // for every side of the room
        int otherSideX, otherSideY;
        for (int i = 0; i < 4; i++) {
            // calculate coordinates for the adjacent grid cell
            otherSideX = roomList[roomIndex].getPosX() + round(sin(i * M_PI / 2));
            otherSideY = roomList[roomIndex].getPosY() - round(cos(i * M_PI / 2));

            bool isOccupied = false;
            // check for a room in the cell: for every room
            for (int j = 0; j < size(roomList); j++) {
                // if the room coordinates are the same as the cell coordinates
                if (roomList[j].getPosX() == otherSideX && roomList[j].getPosY() == otherSideY) {
                    // the cell is occupied
                    isOccupied = true;
                }
            }

            // if the cell is not occupied
            if (!isOccupied) {
                // the room is not surrounded, hence has at least one free side
                isSurrounded = false;
            }
        }

        // if the room is not surrounded
        if (!isSurrounded)
            // an available room is founded
            availableRoomFounded = true;
    }

    // return the index of the available room
    return roomIndex;
}

int FloorMap::pickFreeSide(int roomIndex) {
    // create a list of all room's free side indexes
    std::vector<int> freeSideIndexList;

    // for every adjacent cell
    int otherSideX, otherSideY;
    for (int i = 0; i < 4; i++) {
        // calculate coordinates for the adjacent grid cell
        otherSideX = roomList[roomIndex].getPosX() + round(sin(i * M_PI / 2));
        otherSideY = roomList[roomIndex].getPosY() - round(cos(i * M_PI / 2));

        bool isOccupied = false;
        // for every room
        for (int j = 0; j < size(roomList); j++) {
            // if the room coordinates are the same as the cell coordinates
            if (roomList[j].getPosX() == otherSideX && roomList[j].getPosY() == otherSideY) {
                // the cell is occupied
                isOccupied = true;
            }
        }

        // if the cell is not occupied
        if (!isOccupied) {
            // add free side index to side list
            freeSideIndexList.push_back(i);
        }
    }

    // generate a random number from 0 to length of free sides
    int freeSide = rand() % size(freeSideIndexList);

    // return a random side
    return freeSideIndexList[freeSide];
}

void FloorMap::generateRoom(int roomIndex, int sideIndex, int newRoomIndex) {
    // calculate new room's grid coordinates
    int otherSideX = roomList[roomIndex].getPosX() + round(sin(sideIndex * M_PI / 2));
    int otherSideY = roomList[roomIndex].getPosY() - round(cos(sideIndex * M_PI / 2));

    roomList.push_back(*new Room(otherSideX, otherSideY));

    // assign adjacent room index to start and new room
    roomList[roomIndex].doors[sideIndex] = newRoomIndex;
    roomList[newRoomIndex].doors[(sideIndex + 2) % 4] = roomIndex;
}

void FloorMap::setStartAndEndRooms() {
    // select one random room from all terminal rooms
    indexEndRoom = TerminalRoomIndex();

    int oldPathLength = -1;
    int newPathLength = 0;

    // while back and forth paths gives different length
    while (oldPathLength != newPathLength) {
        oldPathLength = newPathLength;
        indexStartRoom = indexEndRoom;

        // reset path length
        setLongestPathLength(0);
        // from start room, visit recursively all adjacent rooms
        visitAdjacentRooms(indexStartRoom);
        // calculate new path length
        newPathLength = getLongestPathLength();
    }
}

int FloorMap::TerminalRoomIndex() {
    // list of all terminal rooms
    std::vector<int> terminalRoomIndexes;

    // counter
    int numAdjacentRooms;
    // for every room
    for (int i = 0; i < numRooms; i++) {
        // count number of connections
        numAdjacentRooms = 0;

        // for every side
        for (int j = 0; j < 4; j++) {
            // if there's a connection
            if (roomList[i].doors[j] != -1) {
                // increment counter
                numAdjacentRooms++;
            }
        }

        // if room has only one connection
        if (numAdjacentRooms == 1) {
            // is a terminal room
            terminalRoomIndexes.emplace_back(i);
        }
    }

    // return one random index room from the list of all terminal rooms
    int index = rand() % size(terminalRoomIndexes);
    return terminalRoomIndexes[index];
}

int FloorMap::visitAdjacentRooms(int index, int prev, int dist) {
    bool isTerminalRoom = true;

    // for every side
    for (int i = 0; i < 4; i++) {
        // if there's a connection with another room, except for the previous
        if (roomList[index].doors[i] != -1 && i != prev) {
            // the room is not terminal
            isTerminalRoom = false;

            // visit that room
            visitAdjacentRooms(roomList[index].doors[i], (i + 2) % 4, dist + 1);
        }
    }

    // if the room is terminal and the path founded is longer than the previous one
    if (isTerminalRoom && dist >= getLongestPathLength()) {
        // this room become the end room
        indexEndRoom = index;

        // and new longest path is set
        setLongestPathLength(dist);
    }
    return 0;
}
