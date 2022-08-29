//
// Created by longo on 24/07/2022.
//

#include "StatePause.h"

StatePause::StatePause(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Pause Screen/Pause Screen Blank.png");
}

void StatePause::eventHandling(sf::Event event, sf::RenderWindow &window) {
    resumeTextBtn.updateBtn(window);
    exitTextBtn.updateBtn(window);
    settingsTextBtn.updateBtn(window);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Play);

    else if (event.type == sf::Event::MouseButtonReleased) {
        if (resumeTextBtn.btnText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);

        else if (exitTextBtn.btnText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);

        else if (settingsTextBtn.btnText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StatePause::draw(sf::RenderWindow &window) {
    // draw the background
    window.draw(background);

    // and all the buttons
    pauseTextBtn.drawTextBtn(window);
    resumeTextBtn.drawTextBtn(window);
    exitTextBtn.drawTextBtn(window);
    settingsTextBtn.drawTextBtn(window);
}
