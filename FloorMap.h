//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_FLOORMAP_H
#define ACRABSJOURNEY_FLOORMAP_H

class FloorMap {
public:
    FloorMap();
    int getLevel() {
        return level;
    }

    void setLevel(int lev) {
        level = lev;
    }

protected:
    int level;
    std::array<Room> roomlist;

private:
    void generateFloor(level);
    int pickRoom();
    int pickFreeSide(int roomIndex);
    void generateRoom(int roomIndex, int sideIndex, int newRoomIndex);
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
