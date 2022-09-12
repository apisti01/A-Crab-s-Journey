//
// Created by apisti01 on 20/07/22.
//

#ifndef MAIN_CPP_STATETITLESCREEN_H
#define MAIN_CPP_STATETITLESCREEN_H

#include "State.h"
#include "../Game.h"

class StateTitleScreen : public State {
public:
    explicit StateTitleScreen(Game *game);

    ~StateTitleScreen() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    // background
    SpriteButton background = {"Assets/GameStates/MainMenu/Background.png", 1, {.50f, .50f}};

    TextButton titleText = {"A Crab's Journey", 280, {.50f, .46f}};
    TextButton pressBtnText = {"Press any key to continue", 90, {.50f, .65f}};

    float timer = 0;
};


#endif //MAIN_CPP_STATETITLESCREEN_H
