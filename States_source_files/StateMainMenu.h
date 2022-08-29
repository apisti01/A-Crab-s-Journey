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
    Button titleBtn = {"Game States/Main Menu/A Crab's Journey Texture.png", 1, 1920 / 2, 240, false};
    Button newGameBtn = {"Game States/Main Menu/New Game Texture.png", 0.6, 1920 / 2, 420};
    Button loadGameBtn = {"Game States/Main Menu/Load Game Texture.png", 0.6, 1920 / 2, 570};
    Button pearlShopBtn = {"Game States/Main Menu/Pearl Shop Texture.png", 0.6, 1920 / 2, 720};
    Button backToSurfaceBtn = {"Game States/Main Menu/Back to Surface Texture.png", 0.6, 1920 / 2, 870};
    Button creditsBtn = {"Game States/Main Menu/Credits Texture.png", 0.3, 150, 150};
    Button settingsBtn = {"Game States/Main Menu/Settings Texture.png", 0.3, 1920 - 150, 150};
};


#endif //MAIN_CPP_STATEMAINMENU_H
