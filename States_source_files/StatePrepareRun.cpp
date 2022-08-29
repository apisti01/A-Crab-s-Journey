//
// Created by longo on 29/08/2022.
//

#include "StatePrepareRun.h"

StatePrepareRun::StatePrepareRun(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");
}

void StatePrepareRun::eventHandling(sf::Event event, sf::RenderWindow &window) {
    startRunBtn.updateBtn(window);

    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (startRunBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            game->map = std::make_unique<FloorMap>(selectedCharacter,
                                                   Game::getInstance()->globalProgress.habitats[selectedMap].name, 1,
                                                   &(game->bestiary));
            game->changeState(StateType::Play);
        }
    }
}

void StatePrepareRun::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    startRunBtn.drawBtn(window);
}
