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
    explicit StateMainMenu(Game *game);

    ~StateMainMenu() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect{0, 0, 1920, 1080}};

    // text buttons
    Button titleTextBtn = {"A Crab's Journey", game->font, 240, {1920 / 2, 175}};
    Button newGameTextBtn = {"New Game", game->font, 150, {1920 / 2, 400}};
    Button loadGameTextBtn = {"Load Game", game->font, 150, {1920 / 2, 550}};
    Button pearlShopTextBtn = {"Pearl Shop", game->font, 150, {1920 / 2, 700}};
    Button backToSurfaceTextBtn = {"Back to Surface", game->font, 150, {1920 / 2, 850}};
    // icon Buttons
    Button creditsBtn = {"Game States/Main Menu/Credits Texture.png", 0.3, {175, 175}};
    Button settingsBtn = {"Game States/Main Menu/Settings Texture.png", 0.3, {1920 - 175, 175}};
};


#endif //MAIN_CPP_STATEMAINMENU_H
