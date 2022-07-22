//
// Created by apisti01 on 21/07/22.
//

#ifndef MAIN_CPP_STATEPLAY_H
#define MAIN_CPP_STATEPLAY_H

#include "State.h"

class StatePlay : public State{
public:
    // Constructor and Destructor
    explicit StatePlay(Game *game);
    ~StatePlay() override = default;

    void eventHandling(sf::Event event) override;

    void update() override;

    void draw(sf::RenderWindow &window) override;
};


#endif //MAIN_CPP_STATEPLAY_H
