//
// Created by apisti01 on 20/07/22.
//

#ifndef MAIN_CPP_STATEMAINMENU_H
#define MAIN_CPP_STATEMAINMENU_H

#include "State.h"

class StateMainMenu : public State {
public:
    explicit StateMainMenu(Game* game);
    ~StateMainMenu() override = default;

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
    sf::RectangleShape titleBtn, newGameBtn, loadGameBtn, pearlShopBtn, backToSurfaceBtn;
    sf::Texture titleBtnTexture, newGameBtnTexture, loadGameBtnTexture, pearlShopBtnTexture, backToSurfaceBtnTexture;

    sf::RectangleShape creditsBtn, settingsBtn;
    sf::Texture creditsBtnTexture, settingsBtnTexture;
};


#endif //MAIN_CPP_STATEMAINMENU_H
