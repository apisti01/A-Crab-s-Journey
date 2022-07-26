//
// Created by longo on 24/07/2022.
//

#include "Game.h"
#include "StateDisplayMap.h"

StateDisplayMap::StateDisplayMap(Game *game) : State(game), unit(150.0) {
    for (int i = 0; i < game->map->roomList.size(); i++) {
        // room
        int posX = game->map->roomList[0].getWidth() / 2 + game->map->roomList[i].getPosX() * unit;
        int posY = game->map->roomList[0].getHeight() / 2 + game->map->roomList[i].getPosY() * unit;

        sf::RectangleShape newRoom(sf::Vector2f(unit * 0.8, unit * 0.8));
        newRoom.setOrigin(unit * 0.4, unit * 0.4);
        newRoom.setOutlineColor(sf::Color::Black);
        newRoom.setOutlineThickness(3);
        newRoom.setPosition(posX, posY);
        newRoom.setFillColor(sf::Color::White);
        roomShapes.emplace_back(newRoom);

        /*
        for (int j = 0; j < 4; j++) {
            if (game->map->roomList[i].doors[j] != -1) {
                sf::RectangleShape newDoor(sf::Vector2f(unit * 0.2 * sin(j * M_PI / 2), unit * 0.2 * cos(j * M_PI / 2)));
                newDoor.setOutlineColor(sf::Color::Black);
                newDoor.setOutlineThickness(3);
                newDoor.setPosition(posX + unit * 0.4 * sin(j * M_PI / 2), posY - unit * 0.6 * cos(j * M_PI / 2));
                newDoor.setFillColor(sf::Color::White);
                roomShapes.emplace_back(newDoor);
            }
        }
        */

        // room index
        sf::Text text(to_string(i), game->font);
        text.setCharacterSize(unit * 0.4);
        text.setPosition(posX - unit * 0.1, posY - unit * 0.3);
        text.setFillColor(sf::Color::Black);
        roomTextNumbers.emplace_back(text);
    }

    // highlight start, end and shop room
    startPointer.setSize(sf::Vector2f{ unit / 5, unit / 5 });
    startPointer.setPosition(game->map->roomList[0].getWidth() / 2 + game->map->roomList[game->map->startRoomIndex].getPosX() * unit - unit * 0.4,
                             game->map->roomList[0].getHeight() / 2 + game->map->roomList[game->map->startRoomIndex].getPosY() * unit - unit * 0.4);
    startPointer.setFillColor(sf::Color::Green);

    endPointer.setSize(sf::Vector2f{ unit / 5, unit / 5 });
    endPointer.setPosition(game->map->roomList[0].getWidth() / 2 + game->map->roomList[game->map->endRoomIndex].getPosX() * unit - unit * 0.4,
                             game->map->roomList[0].getHeight() / 2 + game->map->roomList[game->map->endRoomIndex].getPosY() * unit - unit * 0.4);
    endPointer.setFillColor(sf::Color::Red);

    shopPointer.setSize(sf::Vector2f{ unit / 5, unit / 5 });
    shopPointer.setOrigin(0, unit / 5);
    shopPointer.setPosition(game->map->roomList[0].getWidth() / 2 + game->map->roomList[game->map->shopRoomIndex].getPosX() * unit - unit * 0.4,
                             game->map->roomList[0].getHeight() / 2 + game->map->roomList[game->map->shopRoomIndex].getPosY() * unit + unit * 0.4);
    shopPointer.setFillColor(sf::Color::Yellow);

    currentPointer.setSize(sf::Vector2f{ unit / 5, unit / 5 });
    currentPointer.setOrigin(unit / 5, 0);
    currentPointer.setFillColor(sf::Color::Blue);

    levelCounter.setString(to_string(game->map->getLevel()));
    levelCounter.setFont(game->font);
    levelCounter.setCharacterSize(unit);
    levelCounter.setPosition(unit, unit);
    levelCounter.setFillColor(sf::Color::Black);
}

void StateDisplayMap::eventHandling(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::M || event.key.code == sf::Keyboard::Escape)
            game->changeState(StateType::Play);
    }
}

void StateDisplayMap::draw(sf::RenderWindow &window) {
    // reset canvas
    window.clear(sf::Color::White);

    window.draw(levelCounter);

    // draw the map
    for (int i = 0; i < size(roomShapes); i++) {
        if (game->map->roomList[i].getVisited())
            window.draw(roomShapes[i]);
    }

    for (int i = 0; i < size(roomTextNumbers); i++) {
        if (game->map->roomList[i].getVisited())
            window.draw(roomTextNumbers[i]);
    }

    currentPointer.setPosition(game->map->roomList[0].getWidth() / 2 + game->map->roomList[game->map->currentRoomIndex].getPosX() * unit + unit * 0.4,
                             game->map->roomList[0].getHeight() / 2 + game->map->roomList[game->map->currentRoomIndex].getPosY() * unit - unit * 0.4);

    // highlight special rooms of the game
    if (game->map->roomList[game->map->startRoomIndex].getVisited())
        window.draw(startPointer);
    if (game->map->roomList[game->map->endRoomIndex].getVisited())
        window.draw(endPointer);
    if (game->map->roomList[game->map->shopRoomIndex].getVisited())
        window.draw(shopPointer);
    window.draw(currentPointer);
}
