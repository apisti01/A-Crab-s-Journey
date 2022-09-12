//
// Created by apisti01 on 21/07/22.
//

#ifndef MAIN_CPP_STATEPLAY_H
#define MAIN_CPP_STATEPLAY_H

#include "State.h"
#include "../Game.h"

class StatePlay : public State {
public:
    // Constructor and Destructor
    explicit StatePlay(Game *game);
    ~StatePlay() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    SpriteButton mapIcon = {"Assets/GameStates/Play/Map Icon.png", 0.3, {.65f, .91f}, false};
    SpriteButton bestiaryIcon = {"Assets/GameStates/Play/Bestiary Icon.png", 0.3, {.74f, .91f}, false};

    TextButton nextFloor = {"Press E to go to the next floor", 90, {.50f, .50f}};

    float sec = 0;
};

#endif //MAIN_CPP_STATEPLAY_H
