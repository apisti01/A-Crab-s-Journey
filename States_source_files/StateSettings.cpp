//
// Created by longo on 26/07/2022.
//

#include "../Game.h"
#include "StateSettings.h"


StateSettings::StateSettings(Game *game) : State(game) {
    texture.loadFromFile("Games States/Settings/Settings.png");
    backgroundSprite = { texture, sf::IntRect(0, 0, 1920, 1080) };
}

void StateSettings::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Pause);
}

void StateSettings::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
}