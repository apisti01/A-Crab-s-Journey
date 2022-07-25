//
// Created by longo on 24/07/2022.
//

#include "StatePause.h"
#include "Game.h"

StatePause::StatePause(Game *game) : State(game) {
    backgroundTexture.loadFromFile("../Games States/Pause Screen/Pause Screen.png");
}

void StatePause::eventHandling(sf::Event event) {
    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code) {
            case sf::Keyboard::Escape:
            case sf::Keyboard::Num1:
                game->changeState(StateType::Play);
                break;
            case sf::Keyboard::Num2:
                game->changeState(StateType::MainMenu);
                break;
            case sf::Keyboard::Num3:
                // game->changeState(StateType::Settings);
                break;
        }
    }
}

void StatePause::draw(sf::RenderWindow &window) {
    window.draw(background);
}