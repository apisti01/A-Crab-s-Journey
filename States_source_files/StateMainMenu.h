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
    TextButton titleTextBtn = {"A Crab's Journey", 240, {.50f, .22f}};
    TextButton newGameTextBtn = {"New Game", 120, {.50f, .41f}, true};
    TextButton loadGameTextBtn = {"Load Game", 120, {.50f, .55f}, true};
    TextButton pearlShopTextBtn = {"Pearl Shop", 120, {.50f, .69f}, true};
    TextButton backToSurfaceTextBtn = {"Back to Surface", 120, {.50f, .83f}, true};
    // icon Buttons
    SpriteButton creditsBtn = {"Assets/GameStates/MainMenu/Credits Texture.png", 0.05f, {.08f, .22}, true};
    SpriteButton settingsBtn = {"Assets/GameStates/MainMenu/Settings Texture.png", 0.05f, {.92f, .22}, true};
};


#endif //MAIN_CPP_STATEMAINMENU_H
