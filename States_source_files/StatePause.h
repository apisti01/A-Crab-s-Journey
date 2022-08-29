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
    explicit StatePause(Game* game);
    ~StatePause() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void createStateButton(sf::RectangleShape* btn, sf::Texture btnTexture, float scl, float posX, float posY, bool clickable = false);

    void updateButton(sf::RectangleShape* btn, sf::RenderWindow &window);

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect {0, 0, 1920, 1080} };

    // buttons
    Button pauseBtn = {"Game States/Pause Screen/Pause Texture.png", 1, 1920 / 2, 200, false};
    Button resumeBtn = {"Game States/Pause Screen/Resume Texture.png", 0.75, 1920 / 2, 450};
    Button exitBtn = {"Game States/Pause Screen/Exit Texture.png", 0.75, 1920 / 2, 650};
    Button settingsBtn = {"Game States/Pause Screen/Settings Texture.png", 0.75, 1920 / 2, 850};
};


#endif //ACRABSJOURNEY_STATEPAUSE_H
