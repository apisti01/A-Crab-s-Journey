//
// Created by apisti01 on 20/07/22.
//

#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *game) : State(game) {}

void StateMainMenu::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    // update the buttons
    titleTextBtn.update(window);
    newGameTextBtn.update(window);
    loadGameTextBtn.update(window);
    pearlShopTextBtn.update(window);
    backToSurfaceTextBtn.update(window);
    creditsBtn.update(window);
    settingsBtn.update(window);
}

void StateMainMenu::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (newGameTextBtn.text.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // go to the prepare run state
            game->changeState(StateType::PrepareRun);
        }

        // load game
        else if (loadGameTextBtn.text.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // TODO load a saved game
        } else if (pearlShopTextBtn.text.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::PearlShop);

        else if (backToSurfaceTextBtn.text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // update the global progress file
            game->globalProgress.updateTxtFile();
            game->bestiary.updateTxtFile();

            // quit the game
            window.close();
        }

        // go to the credits
        else if (creditsBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // TODO: add a credits game state
        }

        // go to the settings
        else if (settingsBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    // draw background
    background.draw(window);

    // and all the buttons
    titleTextBtn.draw(window);
    newGameTextBtn.draw(window);
    loadGameTextBtn.draw(window);
    pearlShopTextBtn.draw(window);
    backToSurfaceTextBtn.draw(window);
    creditsBtn.draw(window);
    settingsBtn.draw(window);
}
