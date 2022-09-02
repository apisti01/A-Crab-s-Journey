//
// Created by longo on 29/08/2022.
//

#include "StatePrepareRun.h"

StatePrepareRun::StatePrepareRun(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");
}

void StatePrepareRun::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    startRunTextBtn.update(window);
    backBtn.update(window);
}

void StatePrepareRun::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (startRunTextBtn.text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            game->map = std::make_unique<FloorMap>(selectedCharacter, game->globalProgress.habitats[selectedMap].name,
                                                   1, game->bestiary);
            game->changeState(StateType::Play);
        }

        else if (backBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);
    }

    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::MainMenu);
}

void StatePrepareRun::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    startRunTextBtn.draw(window);
    backBtn.draw(window);
}
