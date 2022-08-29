//
// Created by apisti01 on 21/07/22.
//

#include "../Game.h"
#include "StatePlay.h"

StatePlay::StatePlay(Game *game) : State(game) {
    mapIconTexture.loadFromFile("Game States/Game/Map Icon.png");
    float mapIconScl = 0.25;
    mapIcon.setPosition(1920 - 700, 1080 - 75);
    mapIcon.setScale(mapIconScl, mapIconScl);
    mapIcon.setOrigin(mapIconTexture.getSize().x / 2, mapIconTexture.getSize().y / 2);
    mapIcon.setSize(sf::Vector2f(mapIconTexture.getSize().x, mapIconTexture.getSize().y));
    mapIcon.setTexture(&mapIconTexture);
}

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

                // if player has completed the floor
                else if (game->map->floorCompleted())
                    game->map = std::make_unique<FloorMap>(game->player->characterIndex, game->map->mapType, game->map->getLevel() + 1, &game->bestiary);
                break;
        }
    }
}

void StatePlay::update(int deltaTime, bool clicked) {
    game->map->update(deltaTime, clicked);
}

void StatePlay::draw(sf::RenderWindow &window) {
    game->map->draw(window);

    window.draw(mapIcon);
}
