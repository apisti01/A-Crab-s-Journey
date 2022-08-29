//
// Created by apisti01 on 21/07/22.
//

#ifndef MAIN_CPP_STATEPLAY_H
#define MAIN_CPP_STATEPLAY_H

#include "State.h"
#include "../Button.h"

class StatePlay : public State {
public:
    // Constructor and Destructor
    explicit StatePlay(Game *game);
    ~StatePlay() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    Button mapIcon = {"Game States/Play/Map Icon.png", 0.3, {1920 - 675, 1080 - 100}, false};
    Button bestiaryIcon = {"Game States/Play/Bestiary Icon.png", 0.3, {1920 - 500, 1080 - 100}, false};
};

#endif //MAIN_CPP_STATEPLAY_H
