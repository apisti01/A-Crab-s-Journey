//
// Created by apisti01 on 04/08/22.
//

#ifndef MAIN_CPP_ENEMYFACTORY_H
#define MAIN_CPP_ENEMYFACTORY_H

#include "../Room.h"

class EnemyFactory {
public:
    // FIXME: MAYBE THEY SHOULD ALL BE STATIC, TO DECIDE ONCE FINISHED WRITING

    // return the final list of the enemies in the room, already in the correct position
    static std::list<std::unique_ptr<Enemy>> fillRoomWithEnemies(Bestiary* bestiary, Room *room, std::string mapType, int level);

private:
    // decide the single enemy based on the mapType
    static std::unique_ptr<Enemy> selectRandomEnemy(Bestiary* bestiary, std::string mapType, int level);

    // put the enemy in the right position
    static void placeEnemy(Enemy *enemy, Room *room);
};

#endif //MAIN_CPP_ENEMYFACTORY_H
