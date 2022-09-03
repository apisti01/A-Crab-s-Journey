//
// Created by apisti01 on 21/07/22.
//

#include "../Game.h"
#include "StatePlay.h"

StatePlay::StatePlay(Game *game) : State(game) {}

void StatePlay::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
            case sf::Keyboard::P:
                game->changeState(StateType::Pause);
                break;
            case sf::Keyboard::M:
                game->changeState(StateType::DisplayMap);
                break;
            case sf::Keyboard::I:
                game->changeState(StateType::ManageInventory);
                break;
            case sf::Keyboard::B:
                game->changeState(StateType::Bestiary);
                break;
            case sf::Keyboard::E:
                // if player is near the shop
                if (game->map->isPlayerNearShop() && !game->map->roomList[game->map->currentRoomIndex]->getCage())
                    game->changeState(StateType::Shop);
                break;

            case sf::Keyboard::L:
                // if player has completed the floor
                if (game->map->floorCompleted()) {
                    auto tmp = std::make_unique<FloorMap>(game->player->characterIndex, game->map->mapType,
                                                           game->map->getLevel() + 1);
                    if(tmp)
                        game->map = std::move(tmp);
                }
                break;
        }
    }
}

void StatePlay::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    game->map->update(deltaTime, clicked);
}

void StatePlay::draw(sf::RenderWindow &window) {
    game->map->draw(window);

    mapIcon.drawBtn(window);
    bestiaryIcon.drawBtn(window);
}
