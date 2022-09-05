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
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect{0, 0, 1920, 1080}};

    // text buttons
    TextButton titleText = {"Game Over", game->font, 240, {1920 / 2, 175}};
    TextButton returnTextBtn = {"Return to Main Menu", game->font, 180, {1920 / 2, 1080 - 150}, true};

    SpriteButton pearlsIcon = {"Game States/Pearl.png", 0.05, {1920 / 2 - 100, 450}};
    TextButton pearlsGained = {"0", game->font, 180, {1920 / 2 + 100, 450}};

    int p = 42;
    int s = 2;
    float t = 0;
};


#endif //ACRABSJOURNEY_STATEGAMEOVER_H
