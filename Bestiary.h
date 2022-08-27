//
// Created by apisti01 on 26/08/22.
//

#ifndef MAIN_CPP_BESTIARY_H
#define MAIN_CPP_BESTIARY_H

#include <map>
#include "Observer.h"

class Bestiary : public Observer {
public:
    // constructor and destructor
    Bestiary();
    ~Bestiary() override = default;

    void update(Enemy *enemy) override;
    void update(Room *room) override;

private:
    // map of strings for every enemy and the state of knowledge they are (?)
    std::map<std::string, int> knowledge;

};


#endif //MAIN_CPP_BESTIARY_H
