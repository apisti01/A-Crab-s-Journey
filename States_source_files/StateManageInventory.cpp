//
// Created by longo on 26/07/2022.
//

#include "StateManageInventory.h"

StateManageInventory::StateManageInventory(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Assets/GameStates/Inventory/Background.png");
}

void StateManageInventory::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::I:
            case sf::Keyboard::Escape:
                game->changeState(StateType::Play);
                break;
            case sf::Keyboard::M: {
                game->changeState(StateType::DisplayMap);
                break;
            case sf::Keyboard::B:
                game->changeState(StateType::Bestiary);
                break;
            case sf::Keyboard::P:
                game->changeState(StateType::Pause);
                break;
            }
        }
    }

}

void StateManageInventory::draw(sf::RenderWindow &window) {
    window.draw(background);
}
