//
// Created by apisti01 on 20/07/22.
//

#ifndef MAIN_CPP_STATEMAINMENU_H
#define MAIN_CPP_STATEMAINMENU_H

#include "State.h"
#include "../Game.h"

class StateMainMenu : public State {
public:
    explicit StateMainMenu(Game *game);

    ~StateMainMenu() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect{0, 0, 1920, 1080}};

    // text buttons
    TextButton titleTextBtn = {"A Crab's Journey", game->font, 240, {1920 / 2, 250}};
    TextButton newGameTextBtn = {"New Game", game->font, 150, {1920 / 2, 450}, true};
    TextButton loadGameTextBtn = {"Load Game", game->font, 150, {1920 / 2, 600}, true};
    TextButton pearlShopTextBtn = {"Pearl Shop", game->font, 150, {1920 / 2, 750}, true};
    TextButton backToSurfaceTextBtn = {"Back to Surface", game->font, 150, {1920 / 2, 900}, true};
    // icon Buttons
    SpriteButton creditsBtn = {"Game States/Main Menu/Credits Texture.png", 0.05, {150, 250}, true};
    SpriteButton settingsBtn = {"Game States/Main Menu/Settings Texture.png", 0.05, {1920 - 150, 250}, true};
};


#endif //MAIN_CPP_STATEMAINMENU_H
