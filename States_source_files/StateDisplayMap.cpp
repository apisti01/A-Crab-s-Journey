//
// Created by longo on 24/07/2022.
//

#include "StateDisplayMap.h"

StateDisplayMap::StateDisplayMap(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Assets/GameStates/DisplayMap/" + game->map->mapType + "/Background Texture.png");
    roomTexture.loadFromFile("Assets/GameStates/DisplayMap/Room Texture.png");

    sf::Sprite room;
    sf::Vector2f pos;
    sf::Vector2f center = { (game->map->minX + game->map->maxX) / 2, (game->map->minY + game->map->maxY) / 2 };
    unit = 600 / (game->map->maxY - game->map->minY + 1);
    if (unit > 400)
        unit = 400;
    float scl = unit / (roomTexture.getSize().x * 1.25);

    for (int i = 0; i < size(game->map->roomList); i++) {
        if (game->map->roomList[i]->getVisited()) {
            pos = { 1920 / 2 + float((game->map->roomList[i]->getPosX() - center.x - 0.5) * unit),
                    700 + float((game->map->roomList[i]->getPosY() - center.y - 0.5) * unit)};
            room.setTexture(roomTexture);
            room.setPosition(pos);
            room.setScale(scl, scl);
            rooms.push_back(room);
        }
    }
}

void StateDisplayMap::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    mapText.update(window);
    levelText.update(window);
    backBtn.update(window);
}

void StateDisplayMap::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::M:
            case sf::Keyboard::Escape:
                game->changeState(StateType::Play);
                break;
            case sf::Keyboard::B:
                game->changeState(StateType::Bestiary);
                break;
            case sf::Keyboard::I:
                game->changeState(StateType::ManageInventory);
                break;
            case sf::Keyboard::P:
                game->changeState(StateType::Pause);
                break;
        }
    }

    else if (event.type == sf::Event::MouseButtonReleased) {
        if (backBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);
    }
}

void StateDisplayMap::draw(sf::RenderWindow &window) {
    // draw the background
    window.draw(background);
    mapText.draw(window);

    // draw the rooms
    for (int i = 0; i < size(rooms); i++)
        window.draw(rooms[i]);

    // and the level text
    levelText.draw(window);

    backBtn.draw(window);
}
