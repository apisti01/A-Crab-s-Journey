//
// Created by apisti01 on 26/08/22.
//

#ifndef MAIN_CPP_BESTIARY_H
#define MAIN_CPP_BESTIARY_H

#include "Observer.h"
#include "Enemy_source_files/Enemy.h"

struct Beast {
    int id;
    bool discovered;
    std::string name, type;
    float health, armor, strength, speed;
    std::vector<std::string> habitats;
    std::string description;
    int triggerRange, attackTimer;
};

class Bestiary : public Observer {
public:
    // constructor and destructor
    Bestiary();
    ~Bestiary() override = default;

    void update(Room *room) override;
    void update(Enemy *enemy) override;

    // map of data of all the enemies in the game
    std::vector<Beast> beasts;

private:
    void createFile();
    void readFile();
};


#endif //MAIN_CPP_BESTIARY_H
