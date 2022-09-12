//
// Created by longo on 24/07/2022.
//

#ifndef ACRABSJOURNEY_STATEPAUSE_H
#define ACRABSJOURNEY_STATEPAUSE_H

#include "State.h"
#include "../Game.h"

class StatePause : public State {
public:
    explicit StatePause(Game *game);

    ~StatePause() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    // background
    SpriteButton background = {"Assets/GameStates/PauseScreen/Background.png", 1, {.50f, .50f}};

    // buttons
    TextButton pauseTextBtn = {"Pause", 210, {.50f, .16f}};
    TextButton resumeTextBtn = {"Resume", 150, {.50f, .39f}, true};
    TextButton exitTextBtn = {"Exit", 150, {.50f, .56f}, true};
    TextButton settingsTextBtn = {"Settings", 150, {.50f, .72f}, true};
};


#endif //ACRABSJOURNEY_STATEPAUSE_H
