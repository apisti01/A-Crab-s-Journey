//
// Created by longo on 26/07/2022.
//

#include "Game.h"
#include "StateManageInventory.h"

StateManageInventory::StateManageInventory(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Inventory/Inventory.png");
}

void StateManageInventory::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Play);
}

void StateManageInventory::draw(sf::RenderWindow &window) {
    window.draw(background);
}
