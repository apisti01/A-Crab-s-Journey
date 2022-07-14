//
// Created by longo on 07/07/2022.
//

#include "Room.h"

using namespace std;

Room::Room(int posX, int posY) : posX(posX), posY(posY), XpReward(XpReward = 0), isCage(isCage = false),
           isStartRoom(isStartRoom = false), isBossRoom(isBossRoom = false), isShopRoom(isShopRoom = false) {
    // doors are all initially closed
    doors = {-1, -1, -1, -1};

    // TODO: create list of obstacles

    // TODO: if it isn't the start room, create list of enemies
    if (!getStartRoom()) {

    }
};

/*
void Room::enterCageMode(Player &player) {
    // if player enter the room and there are enemies
    if (player.getPosX() > wallDepth && player.getPosX() < roomWidth - wallDepth && player.getPosY() > wallDepth && player.getPosY() < roomHeight - wallDepth && size(enemyList) != 0) {
        isCage = true;
    }
}

void Room::exitCageMode() {
    // when the player kills an enemy, if it's the last in the room
    if (size(enemyList) != 0) {
        isCage = false;
    }
}
*/