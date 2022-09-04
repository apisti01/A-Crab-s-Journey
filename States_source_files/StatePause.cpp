//
// Created by longo on 24/07/2022.
//

#include "StatePause.h"

StatePause::StatePause(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Pause Screen/Pause Screen Blank.png");
}

void StatePause::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    pauseTextBtn.update(window);
    resumeTextBtn.update(window);
    exitTextBtn.update(window);
    settingsTextBtn.update(window);
}

void StatePause::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Play);

    else if (event.type == sf::Event::MouseButtonReleased) {
        if (resumeTextBtn.text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);

        else if (exitTextBtn.text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);

        else if (settingsTextBtn.text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StatePause::draw(sf::RenderWindow &window) {
    // draw the background
    window.draw(background);

    // and all the buttons
    pauseTextBtn.draw(window);
    resumeTextBtn.draw(window);
    exitTextBtn.draw(window);
    settingsTextBtn.draw(window);
}
