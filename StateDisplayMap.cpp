//
// Created by longo on 24/07/2022.
//

#include <iostream>

#include "StateDisplayMap.h"
#include "Game.h"

StateDisplayMap::StateDisplayMap(Game *game) : State(game) {
    for (int i = 0; i < game->map->roomList.size(); i++) {
        // room
        int posX = (game->map->roomList[i].getPosX() + 8) * 100;
        int posY = (game->map->roomList[i].getPosY() + 4.5) * 100;

        sf::RectangleShape newRoom(sf::Vector2f(80, 80));
        newRoom.setOrigin(40, 40);
        newRoom.setOutlineColor(sf::Color::Black);
        newRoom.setOutlineThickness(3);
        newRoom.setPosition(posX, posY);
        newRoom.setFillColor(sf::Color::White);
        roomShapes.emplace_back(newRoom);

        for (int j = 0; j < 4; j++) {
            if (game->map->roomList[i].doors[j] != -1) {
                sf::RectangleShape newDoor(sf::Vector2f(20 * sin(j * M_PI / 2), 20 * cos(j * M_PI / 2)));
                newDoor.setOutlineColor(sf::Color::Black);
                newDoor.setOutlineThickness(3);
                newDoor.setPosition(posX + 40 * sin(j * M_PI / 2), posY - 60 * cos(j * M_PI / 2));
                newDoor.setFillColor(sf::Color::White);
                roomShapes.emplace_back(newDoor);
            }
        }

        // room index
        sf::Text text(to_string(i), game->font);
        text.setCharacterSize(40);
        text.setPosition((game->map->roomList[i].getPosX() + 8) * 100 - 10, (game->map->roomList[i].getPosY() + 4.5) * 100 - 30);
        text.setFillColor(sf::Color::Black);
        roomTextNumbers.emplace_back(text);
    }

    // highlight start, end and shop room
    startPointer.setRadius(10);
    startPointer.setPosition((game->map->roomList[game->map->startRoomIndex].getPosX() + 8) * 100 - 35, (game->map->roomList[game->map->startRoomIndex].getPosY() + 4.5) * 100 - 35);
    startPointer.setFillColor(sf::Color::Green);

    endPointer.setRadius(10);
    endPointer.setPosition((game->map->roomList[game->map->endRoomIndex].getPosX() + 8) * 100 - 35, (game->map->roomList[game->map->endRoomIndex].getPosY() + 4.5) * 100 - 35);
    endPointer.setFillColor(sf::Color::Red);

    shopPointer.setRadius(10);
    shopPointer.setPosition((game->map->roomList[game->map->shopRoomIndex].getPosX() + 8) * 100 + 15, (game->map->roomList[game->map->shopRoomIndex].getPosY() + 4.5) * 100 - 35);
    shopPointer.setFillColor(sf::Color::Yellow);

    currentPointer.setRadius(10);
    currentPointer.setFillColor(sf::Color::Blue);
}

void StateDisplayMap::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
        game->changeState(StateType::Play);
}

void StateDisplayMap::draw(sf::RenderWindow &window) {
    // reset canvas
    window.clear(sf::Color::White);

    // draw the map
    for (int i = 0; i < size(roomShapes); i++)
        window.draw(roomShapes[i]);
    for (int i = 0; i < size(roomTextNumbers); i++)
        window.draw(roomTextNumbers[i]);

    currentPointer.setPosition((game->map->roomList[game->map->currentRoomIndex].getPosX() + 8) * 100 + 15, (game->map->roomList[game->map->currentRoomIndex].getPosY() + 4.5) * 100 + 15);

    // highlight special rooms of the game
    window.draw(startPointer);
    window.draw(endPointer);
    window.draw(shopPointer);
    window.draw(currentPointer);
}
