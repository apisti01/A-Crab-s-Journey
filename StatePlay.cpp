//
// Created by apisti01 on 21/07/22.
//

#include "StatePlay.h"
#include "Game.h"

StatePlay::StatePlay(Game *game) : State(game) {}

void StatePlay::eventHandling(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::M:
                game->changeState(StateType::DisplayMap);
                break;
            case sf::Keyboard::Escape:
            case sf::Keyboard::P:
                game->changeState(StateType::Pause);
                break;
            case sf::Keyboard::I:
                game->changeState(StateType::ManageInventory);
                break;
            case sf::Keyboard::E:
                // FIXME player must be near the shop
                if (game->map->currentRoomIndex == game->map->shopRoomIndex /* && game->map->roomList[game->map->currentRoomIndex].enemyList.empty() */)
                    game->changeState(StateType::Shop);
                break;
        }
    }
}

void StatePlay::update(int deltaTime) {
    game->map->update(deltaTime);
}

void StatePlay::draw(sf::RenderWindow &window) {
    game->map->draw(window);
}
