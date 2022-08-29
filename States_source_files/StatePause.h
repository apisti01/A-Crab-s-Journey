//
// Created by longo on 24/07/2022.
//

#ifndef ACRABSJOURNEY_STATEPAUSE_H
#define ACRABSJOURNEY_STATEPAUSE_H

#include "../Game.h"
#include "../Button.h"
#include "State.h"

class StatePause : public State {
public:
    explicit StatePause(Game *game);

    ~StatePause() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect{0, 0, 1920, 1080}};

    // buttons
    Button pauseTextBtn = {"Pause", game->font, 220, sf::Vector2f{1920 / 2, 150}};
    Button resumeTextBtn = {"Resume", game->font, 160, sf::Vector2f{1920 / 2, 400}};
    Button exitTextBtn = {"Exit", game->font, 160, sf::Vector2f{1920 / 2, 600}};
    Button settingsTextBtn = {"Settings", game->font, 160, sf::Vector2f{1920 / 2, 800}};
};


#endif //ACRABSJOURNEY_STATEPAUSE_H
