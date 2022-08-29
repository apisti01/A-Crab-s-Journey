//
// Created by longo on 26/07/2022.
//

#include "../Game.h"
#include "StateSettings.h"


StateSettings::StateSettings(Game *game) : State(game) {
    texture.loadFromFile("Game States/Pause Screen/Pause Screen Blank.png");
}

void StateSettings::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Pause);
}

void StateSettings::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
}