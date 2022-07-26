//
// Created by longo on 26/07/2022.
//

#include "Game.h"
#include "StatePearlShop.h"


StatePearlShop::StatePearlShop(Game *game) : State(game) {
    texture.loadFromFile("Games States/Pearl Shop/Pearl Shop.png");
    backgroundSprite = { texture, sf::IntRect(0, 0, 1920, 1080) };
}

void StatePearlShop::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::MainMenu);
}

void StatePearlShop::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);
}