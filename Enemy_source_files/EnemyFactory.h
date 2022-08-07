//
// Created by apisti01 on 04/08/22.
//

#ifndef MAIN_CPP_ENEMYFACTORY_H
#define MAIN_CPP_ENEMYFACTORY_H

#include "../Room.h"

class EnemyFactory {
public:
    // XXX MAYBE THEY SHOULD ALL BE STATIC, TO DECIDE ONCE FINISHED WRITING

    // return the final list of the enemies in the room, already in the correct position
    std::list<std::unique_ptr<Enemy>> fillRoomWithEnemies(Room *room, MapType type, int level);

private:
    // decide the single enemy based on the mapType
    std::unique_ptr<Enemy> createSingleEnemy(MapType mapType, int level);

    // put the enemy in the right position
    void locateEnemy(Enemy *enemy, Room *room);

    // function specific for every mapType
    std::unique_ptr<Enemy> coralReefEnemy(int level);
    std::unique_ptr<Enemy> mangroveForestEnemy(int level);
    std::unique_ptr<Enemy> temperateReefEnemy(int level);
    std::unique_ptr<Enemy> kelpForestEnemy(int level);
    std::unique_ptr<Enemy> posidoniaMeadowEnemy(int level);
    std::unique_ptr<Enemy> iceFloeEnemy(int level);
};


#endif //MAIN_CPP_ENEMYFACTORY_H
