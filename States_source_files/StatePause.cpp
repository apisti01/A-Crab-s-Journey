//
// Created by longo on 24/07/2022.
//

#include "StatePause.h"

StatePause::StatePause(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Pause Screen/Pause Screen Blank.png");
}

void StatePause::eventHandling(sf::Event event, sf::RenderWindow &window) {
    resumeBtn.updateBtn(window);
    exitBtn.updateBtn(window);
    settingsBtn.updateBtn(window);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Play);

    else if (event.type == sf::Event::MouseButtonReleased) {
        if (resumeBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);

        else if (exitBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);

        else if (settingsBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StatePause::draw(sf::RenderWindow &window) {
    // draw the background
    window.draw(background);

    // and all the buttons
    resumeBtn.drawBtn(window);
    exitBtn.drawBtn(window);
    settingsBtn.drawBtn(window);
}
