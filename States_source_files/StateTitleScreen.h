//
// Created by apisti01 on 20/07/22.
//

#ifndef MAIN_CPP_STATETITLESCREEN_H
#define MAIN_CPP_STATETITLESCREEN_H

#include "../Game.h"
#include "../Button.h"
#include "State.h"

class StateTitleScreen : public State {
public:
    // Constructor and Destructor
    explicit StateTitleScreen(Game *game);

    ~StateTitleScreen() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect(0, 0, 1920, 1080)};

    Button titleText = {"A Crab's Journey", game->font, 280, {1920 / 2, 500}, false};
    Button pressBtnText = {"Press any key to continue", game->font, 90, {1920 / 2, 700}, false};

    float timer = 0;
};


#endif //MAIN_CPP_STATETITLESCREEN_H
