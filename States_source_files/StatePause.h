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
    Button resumeBtn = {"Games States/Pause Screen/Resume Texture.png", 0.8, 1920 / 2, 300};
    Button exitBtn = {"Games States/Pause Screen/Exit Texture.png", 0.8, 1920 / 2, 500};
    Button settingsBtn = {"Games States/Pause Screen/Settings Texture.png", 0.8, 1920 / 2, 700};
};


#endif //ACRABSJOURNEY_STATEPAUSE_H
