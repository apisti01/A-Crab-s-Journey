//
// Created by apisti01 on 20/07/22.
//

#include "StateMainMenu.h"
#include "../Game.h"

StateMainMenu::StateMainMenu(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Start Menu/Start Menu Blank.png");

    titleBtnTexture.loadFromFile("Games States/Start Menu/A Crab's Journey Texture.png");
    createStateButton(&titleBtn, titleBtnTexture, 1, 1920 / 2, 240, false);
    titleBtn.setTexture(&titleBtnTexture);

    newGameBtnTexture.loadFromFile("Games States/Start Menu/New Game Texture.png");
    createStateButton(&newGameBtn, newGameBtnTexture, 0.6, 1920 / 2, 420);
    newGameBtn.setTexture(&newGameBtnTexture);

    loadGameBtnTexture.loadFromFile("Games States/Start Menu/Load Game Texture.png");
    createStateButton(&loadGameBtn, loadGameBtnTexture, 0.6, 1920 / 2, 570);
    loadGameBtn.setTexture(&loadGameBtnTexture);

    pearlShopBtnTexture.loadFromFile("Games States/Start Menu/Pearl Shop Texture.png");
    createStateButton(&pearlShopBtn, pearlShopBtnTexture, 0.6, 1920 / 2, 720);
    pearlShopBtn.setTexture(&pearlShopBtnTexture);

    backToSurfaceBtnTexture.loadFromFile("Games States/Start Menu/Back to Surface Texture.png");
    createStateButton(&backToSurfaceBtn, backToSurfaceBtnTexture, 0.6, 1920 / 2, 870);
    backToSurfaceBtn.setTexture(&backToSurfaceBtnTexture);

    creditsBtnTexture.loadFromFile("Games States/Start Menu/Credits Texture.png");
    createStateButton(&creditsBtn, creditsBtnTexture, 0.3, 150, 150);
    creditsBtn.setTexture(&creditsBtnTexture);

    settingsBtnTexture.loadFromFile("Games States/Start Menu/Settings Texture.png");
    createStateButton(&settingsBtn, settingsBtnTexture, 0.3, 1920 - 150, 150);
    settingsBtn.setTexture(&settingsBtnTexture);
}

void StateMainMenu::createStateButton(sf::RectangleShape* btn, sf::Texture btnTexture, float scl, float posX, float posY, bool clickable) {
    // TODO: create button class
    btn->setPosition(posX, posY);
    btn->setScale(scl, scl);
    btn->setOrigin(btnTexture.getSize().x / 2, btnTexture.getSize().y / 2);
    btn->setSize(sf::Vector2f(btnTexture.getSize().x, btnTexture.getSize().y));
    if (clickable)
        btn->setFillColor(sf::Color(255, 255, 255, 128));
}

void StateMainMenu::eventHandling(sf::Event event, sf::RenderWindow &window) {
    // update the buttons
    updateButton(&newGameBtn, window);
    updateButton(&loadGameBtn, window);
    updateButton(&pearlShopBtn, window);
    updateButton(&backToSurfaceBtn, window);
    updateButton(&creditsBtn, window);
    updateButton(&settingsBtn, window);

    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (newGameBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            int level = 1;
            game->map = std::make_unique<FloorMap>(level, MapType::CoralReef);
            game->changeState(StateType::Play);
        }

        // TODO load a game saved
        if (loadGameBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            int level = 1;
            game->map = std::make_unique<FloorMap>(level, MapType::CoralReef);
            game->changeState(StateType::Play);
        }

        // TODO go to pearls shop
        if (pearlShopBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::PearlShop);

        // quit the game
        if (backToSurfaceBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            window.close();

        // go to the credits
        if (creditsBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // TODO: add a credits game state
        }

        // go to the settings
        if (settingsBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StateMainMenu::updateButton(sf::RectangleShape* btn, sf::RenderWindow &window) {
    if (btn->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        btn->setFillColor(sf::Color(255, 255, 255, 255));
    else
        btn->setFillColor(sf::Color(255, 255, 255, 128));
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    // and all the buttons
    window.draw(titleBtn);
    window.draw(newGameBtn);
    window.draw(loadGameBtn);
    window.draw(pearlShopBtn);
    window.draw(backToSurfaceBtn);

    window.draw(creditsBtn);
    window.draw(settingsBtn);
}
