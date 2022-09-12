//
// Created by longo on 03/09/2022.
//

#ifndef ACRABSJOURNEY_STATEGAMEOVER_H
#define ACRABSJOURNEY_STATEGAMEOVER_H

#include "State.h"
#include "../Game.h"

class StateGameOver : public State {
public:
    explicit StateGameOver(Game *game);

    ~StateGameOver() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    // background
    SpriteButton background = {"Assets/GameStates/MainMenu/Background.png", 1, {.50f, .50f}};

    // text buttons
    TextButton titleText = {"Game Over", 240, {.50f, .16f}};
    TextButton returnTextBtn = {"Return to MainMenu", 180, {.50f, .86f}, true};

    SpriteButton pearlsIcon = {"Assets/GameStates/Pearl.png", 0.05, {.45f, .42f}};
    TextButton pearlsGained = {"0", 180, {.55f, .42f}};

    int p = 42;
    float s = 2 * log10f(p + 1);
    float t = 0;
};


#endif //ACRABSJOURNEY_STATEGAMEOVER_H
