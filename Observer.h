//
// Created by apisti01 on 26/08/22.
//

#ifndef MAIN_CPP_OBSERVER_H
#define MAIN_CPP_OBSERVER_H

class Enemy;
class Room;

class Observer {
public:
    // constructor and destructor
    Observer() = default;
    virtual ~Observer() = default;

    // update function to modify to behaviour of the concrete observers, overloaded depending on the needs
    virtual void update(Enemy* enemy) = 0;
    virtual void update(Room* room) = 0;

};


#endif // MAIN_CPP_OBSERVER_H
