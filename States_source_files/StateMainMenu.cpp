//
// Created by apisti01 on 20/07/22.
//

#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Start Menu/Start Menu Blank.png");
}

void StateMainMenu::eventHandling(sf::Event event, sf::RenderWindow &window) {
    // update the buttons
    newGameBtn.updateBtn(window);
    loadGameBtn.updateBtn(window);
    pearlShopBtn.updateBtn(window);
    backToSurfaceBtn.updateBtn(window);
    creditsBtn.updateBtn(window);
    settingsBtn.updateBtn(window);

    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (newGameBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            int level = 1;
            game->map = std::make_unique<FloorMap>(level, MapType::CoralReef, &(game->bestiary));
            game->changeState(StateType::Play);
        }

        // TODO load a game saved
        else if (loadGameBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            int level = 1;
            game->map = std::make_unique<FloorMap>(level, MapType::CoralReef, &(game->bestiary));
            game->changeState(StateType::Play);
        }

        else if (pearlShopBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::PearlShop);

        // quit the game
        else if (backToSurfaceBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            window.close();

        // go to the credits
        else if (creditsBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // TODO: add a credits game state
        }

        // go to the settings
        else if (settingsBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    // and all the buttons
    titleBtn.drawBtn(window);
    newGameBtn.drawBtn(window);
    loadGameBtn.drawBtn(window);
    pearlShopBtn.drawBtn(window);
    backToSurfaceBtn.drawBtn(window);
    creditsBtn.drawBtn(window);
    settingsBtn.drawBtn(window);
}
