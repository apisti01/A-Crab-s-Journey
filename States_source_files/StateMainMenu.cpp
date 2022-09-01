//
// Created by apisti01 on 20/07/22.
//

#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");
}

void StateMainMenu::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    // update the buttons
    titleTextBtn.updateBtn(window);
    newGameTextBtn.updateBtn(window);
    loadGameTextBtn.updateBtn(window);
    pearlShopTextBtn.updateBtn(window);
    backToSurfaceTextBtn.updateBtn(window);
    creditsBtn.updateBtn(window);
    settingsBtn.updateBtn(window);
}

void StateMainMenu::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (newGameTextBtn.btnText.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // go to the prepare run state
            game->changeState(StateType::PrepareRun);
        }

        // load game
        else if (loadGameTextBtn.btnText.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // TODO load a saved game
        } else if (pearlShopTextBtn.btnText.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::PearlShop);

        else if (backToSurfaceTextBtn.btnText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // update the global progress file
            game->globalProgress.updateTxtFile();
            game->bestiary.updateTxtFile();

            // quit the game
            window.close();
        }

        // go to the credits
        else if (creditsBtn.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // TODO: add a credits game state
        }

        // go to the settings
        else if (settingsBtn.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    // and all the buttons
    titleTextBtn.drawTextBtn(window);
    newGameTextBtn.drawTextBtn(window);
    loadGameTextBtn.drawTextBtn(window);
    pearlShopTextBtn.drawTextBtn(window);
    backToSurfaceTextBtn.drawTextBtn(window);
    creditsBtn.drawBtn(window);
    settingsBtn.drawBtn(window);
}
