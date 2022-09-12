//
// Created by longo on 26/07/2022.
//

#include "StateSettings.h"

StateSettings::StateSettings(Game *game) : State(game) {}

void StateSettings::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    settingsText.update(window);
    languageText.update(window);
    difficultyText.update(window);
    soundText.update(window);

    backBtn.update(window);
}

void StateSettings::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Pause);

    else if (event.type == sf::Event::MouseButtonReleased) {
        if (backBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);
    }
}

void StateSettings::draw(sf::RenderWindow &window) {
    background.draw(window);

    settingsText.draw(window);
    difficultyText.draw(window);
    languageText.draw(window);
    soundText.draw(window);

    backBtn.draw(window);
}