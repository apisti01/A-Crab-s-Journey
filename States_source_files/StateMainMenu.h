//
// Created by apisti01 on 20/07/22.
//

#ifndef MAIN_CPP_STATEMAINMENU_H
#define MAIN_CPP_STATEMAINMENU_H

#include "../Game.h"
#include "../Button.h"
#include "State.h"

class StateMainMenu : public State {
public:
    explicit StateMainMenu(Game* game);
    ~StateMainMenu() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect {0, 0, 1920, 1080} };

    // buttons
    Button titleBtn = {"Games States/Start Menu/A Crab's Journey Texture.png", 1, 1920 / 2, 240, false};
    Button newGameBtn = {"Games States/Start Menu/New Game Texture.png", 0.6, 1920 / 2, 420};
    Button loadGameBtn = {"Games States/Start Menu/Load Game Texture.png", 0.6, 1920 / 2, 570};
    Button pearlShopBtn = {"Games States/Start Menu/Pearl Shop Texture.png", 0.6, 1920 / 2, 720};
    Button backToSurfaceBtn = {"Games States/Start Menu/Back to Surface Texture.png", 0.6, 1920 / 2, 870};
    Button creditsBtn = {"Games States/Start Menu/Credits Texture.png", 0.3, 150, 150};
    Button settingsBtn = {"Games States/Start Menu/Settings Texture.png", 0.3, 1920 - 150, 150};
};


#endif //MAIN_CPP_STATEMAINMENU_H
