//
// Created by longo on 19/08/2022.
//

#include "StateBestiary.h"
#include "../Game.h"

StateBestiary::StateBestiary(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Bestiary/Bestiary.png");
}

void StateBestiary::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::B:
            case sf::Keyboard::Escape:
                game->changeState(StateType::Play);
                break;
            case sf::Keyboard::M: {
                game->changeState(StateType::DisplayMap);
                break;
            case sf::Keyboard::I:
                game->changeState(StateType::ManageInventory);
                break;
            case sf::Keyboard::P:
                game->changeState(StateType::Pause);
                break;
            }
        }
    }
}

void StateBestiary::draw(sf::RenderWindow &window) {
    window.draw(background);
}
