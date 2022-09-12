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
    SpriteButton background = {"Assets/GameStates/MainMenu/Background.png", 1, {.50f, .50f}};

    // text buttons
    TextButton titleTextBtn = {"A Crab's Journey", 240, {.50f, .24f}};
    TextButton newGameTextBtn = {"New Game", 150, {.50f, .43f}, true};
    TextButton loadGameTextBtn = {"Load Game", 150, {.50f, .57f}, true};
    TextButton pearlShopTextBtn = {"Pearl Shop", 150, {.50f, .71f}, true};
    TextButton backToSurfaceTextBtn = {"Back to Surface", 150, {.50f, .85f}, true};
    // icon Buttons
    SpriteButton creditsBtn = {"Assets/GameStates/MainMenu/Credits Texture.png", 0.05f, {.08f, .25f}, true};
    SpriteButton settingsBtn = {"Assets/GameStates/MainMenu/Settings Texture.png", 0.05f, {.92f, .25f}, true};
};


#endif //MAIN_CPP_STATEMAINMENU_H
