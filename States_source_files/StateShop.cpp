//
// Created by longo on 26/07/2022.
//

#include "StateShop.h"

StateShop::StateShop(Game *game) : State(game) {
    texture.loadFromFile("Game States/Shop/Shop.png");
    backgroundSprite = { texture, sf::IntRect(0, 0, 1920, 1080) };
}

void StateShop::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::E)
           game->changeState(StateType::Play);
    }
}

void StateShop::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
}
