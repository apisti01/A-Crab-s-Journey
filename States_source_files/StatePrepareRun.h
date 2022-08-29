//
// Created by longo on 29/08/2022.
//

#ifndef ACRABSJOURNEY_STATEPREPARERUN_H
#define ACRABSJOURNEY_STATEPREPARERUN_H

#include "../Game.h"
#include "../Button.h"
#include "State.h"

class StatePrepareRun : public State {
public:
    explicit StatePrepareRun(Game* game);
    ~StatePrepareRun() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;
private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect {0, 0, 1920, 1080} };

    Button startRunBtn = { "Game States/Main Menu/New Game Texture.png", 1, 1920 / 2, 240};

    int selectedCharacter = 0;
    int selectedMap = 0;
};


#endif //ACRABSJOURNEY_STATEPREPARERUN_H
