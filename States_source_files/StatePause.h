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
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect{0, 0, 1920, 1080}};

    // buttons
    TextButton pauseTextBtn = {"Pause", game->font, 210, {1920 / 2, 150}};
    TextButton resumeTextBtn = {"Resume", game->font, 150, {1920 / 2, 400}, true};
    TextButton exitTextBtn = {"Exit", game->font, 150, {1920 / 2, 600}, true};
    TextButton settingsTextBtn = {"Settings", game->font, 150, {1920 / 2, 800}, true};
};


#endif //ACRABSJOURNEY_STATEPAUSE_H
