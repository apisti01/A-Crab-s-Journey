//
// Created by apisti01 on 20/07/22.
//

#include "StateMainMenu.h"
#include "../Game.h"

StateMainMenu::StateMainMenu(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Start Menu/Start Menu.png");
}

void StateMainMenu::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Num1: {
                // create new floor
                int level = 1;
                game->map = std::make_unique<FloorMap>(level, MapType::CoralReef);

                game->changeState(StateType::Play);
            }
                break;
            case sf::Keyboard::Num2: {
                // create new floor
                int level = 1;
                game->map = std::make_unique<FloorMap>(level, MapType::CoralReef);

                game->changeState(StateType::Play);
            }
                break;
            case sf::Keyboard::Num3:
                game->changeState(StateType::PearlShop);
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
        }
    }
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    window.draw(background);
}
