//
// Created by apisti01 on 20/07/22.
//

#include "StateMainMenu.h"
#include "../Game.h"

StateMainMenu::StateMainMenu(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Start Menu/Start Menu Blank.png");

    titleBtnTexture.loadFromFile("Games States/Start Menu/A Crab's Journey Texture.png");
    float titleBtnScl = 1;
    titleBtn.setPosition(1920 / 2, 240);
    titleBtn.setScale(titleBtnScl, titleBtnScl);
    titleBtn.setOrigin(titleBtnTexture.getSize().x / 2, titleBtnTexture.getSize().y / 2);
    titleBtn.setSize(sf::Vector2f(titleBtnTexture.getSize().x, titleBtnTexture.getSize().y));
    titleBtn.setTexture(&titleBtnTexture);

    newGameBtnTexture.loadFromFile("Games States/Start Menu/New Game Texture.png");
    float newGameBtnScl = 0.6;
    newGameBtn.setPosition(1920 / 2, 420);
    newGameBtn.setScale(newGameBtnScl, newGameBtnScl);
    newGameBtn.setOrigin(newGameBtnTexture.getSize().x / 2, newGameBtnTexture.getSize().y / 2);
    newGameBtn.setSize(sf::Vector2f(newGameBtnTexture.getSize().x, newGameBtnTexture.getSize().y));
    newGameBtn.setTexture(&newGameBtnTexture);

    loadGameBtnTexture.loadFromFile("Games States/Start Menu/Load Game Texture.png");
    float loadGameBtnScl = 0.6;
    loadGameBtn.setPosition(1920 / 2, 570);
    loadGameBtn.setScale(loadGameBtnScl, loadGameBtnScl);
    loadGameBtn.setOrigin(loadGameBtnTexture.getSize().x / 2, loadGameBtnTexture.getSize().y / 2);
    loadGameBtn.setSize(sf::Vector2f(loadGameBtnTexture.getSize().x, loadGameBtnTexture.getSize().y));
    loadGameBtn.setTexture(&loadGameBtnTexture);

    pearlShopBtnTexture.loadFromFile("Games States/Start Menu/Pearl Shop Texture.png");
    float pearlShopBtnScl = 0.6;
    pearlShopBtn.setPosition(1920 / 2, 720);
    pearlShopBtn.setScale(pearlShopBtnScl, pearlShopBtnScl);
    pearlShopBtn.setOrigin(pearlShopBtnTexture.getSize().x / 2, pearlShopBtnTexture.getSize().y / 2);
    pearlShopBtn.setSize(sf::Vector2f(pearlShopBtnTexture.getSize().x, pearlShopBtnTexture.getSize().y));
    pearlShopBtn.setTexture(&pearlShopBtnTexture);

    backToSurfaceBtnTexture.loadFromFile("Games States/Start Menu/Back to Surface Texture.png");
    float backToSurfaceBtnScl = 0.6;
    backToSurfaceBtn.setPosition(1920 / 2, 870);
    backToSurfaceBtn.setScale(backToSurfaceBtnScl, backToSurfaceBtnScl);
    backToSurfaceBtn.setOrigin(backToSurfaceBtnTexture.getSize().x / 2, backToSurfaceBtnTexture.getSize().y / 2);
    backToSurfaceBtn.setSize(sf::Vector2f(backToSurfaceBtnTexture.getSize().x, backToSurfaceBtnTexture.getSize().y));
    backToSurfaceBtn.setTexture(&backToSurfaceBtnTexture);

    creditsBtnTexture.loadFromFile("Games States/Start Menu/Credits Texture.png");
    float creditsBtnScl = 0.3;
    creditsBtn.setPosition(150, 150);
    creditsBtn.setScale(creditsBtnScl, creditsBtnScl);
    creditsBtn.setOrigin(creditsBtnTexture.getSize().x / 2, creditsBtnTexture.getSize().y / 2);
    creditsBtn.setSize(sf::Vector2f(creditsBtnTexture.getSize().x, creditsBtnTexture.getSize().y));
    creditsBtn.setTexture(&creditsBtnTexture);

    settingsBtnTexture.loadFromFile("Games States/Start Menu/Settings Texture.png");
    float settingsBtnScl = 0.3;
    settingsBtn.setPosition(1920 - 150, 150);
    settingsBtn.setScale(settingsBtnScl, settingsBtnScl);
    settingsBtn.setOrigin(settingsBtnTexture.getSize().x / 2, settingsBtnTexture.getSize().y / 2);
    settingsBtn.setSize(sf::Vector2f(settingsBtnTexture.getSize().x, settingsBtnTexture.getSize().y));
    settingsBtn.setTexture(&settingsBtnTexture);
}

void StateMainMenu::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        if (newGameBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            int level = 1;
            game->map = std::make_unique<FloorMap>(level, MapType::CoralReef);
            game->changeState(StateType::Play);
        }

        if (loadGameBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            int level = 1;
            game->map = std::make_unique<FloorMap>(level, MapType::CoralReef);
            game->changeState(StateType::Play);
        }

        if (pearlShopBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::PearlShop);

        if (backToSurfaceBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            window.close();

        if (creditsBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // TODO: add a credits game state
        }

        if (settingsBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
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
