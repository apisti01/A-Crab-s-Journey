#include <SFML/Graphics.hpp>
#include <iostream>
#include "ctime"
#include "FloorMap.h"
#include "FloorMap.cpp"

int main() {
    // caricamento del font
    sf::Font Rancho;
    if (!Rancho.loadFromFile("Font/Rancho/Rancho.ttf")) {
        cout << "font non caricato" << endl;
        system("pause");
    }

    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "A Crab's Journey");

    // load and set Game's Icon
    sf::Image icon;
    icon.loadFromFile("Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int level = 4;
    std::vector<sf::RectangleShape> roomShapes;
    std::vector<sf::Text> roomTextNumbers;
    sf::CircleShape startPointer;
    sf::CircleShape endPointer;

    FloorMap *floor = new FloorMap(level);

    for (int i = 0; i < floor->roomList.size(); i++) {
        // room
        int posX = (floor->roomList[i].getPosX() + 8) * 100;
        int posY = (floor->roomList[i].getPosY() + 4.5) * 100;

        sf::RectangleShape newRoom(sf::Vector2f(80, 80));
        newRoom.setOrigin(40, 40);
        newRoom.setOutlineColor(sf::Color::Black);
        newRoom.setOutlineThickness(3);
        newRoom.setPosition(posX, posY);
        newRoom.setFillColor(sf::Color::White);
        roomShapes.emplace_back(newRoom);

        for (int j = 0; j < 4; j++) {
            if (floor->roomList[i].doors[j] != -1) {
                sf::RectangleShape newDoor(sf::Vector2f(20 * sin(j * M_PI / 2), 20 * cos(j * M_PI / 2)));
                newDoor.setOutlineColor(sf::Color::Black);
                newDoor.setOutlineThickness(3);
                newDoor.setPosition(posX + 40 * sin(j * M_PI / 2), posY - 60 * cos(j * M_PI / 2));
                newDoor.setFillColor(sf::Color::White);
                roomShapes.emplace_back(newDoor);
            }
        }

        // room index
        sf::Text text(to_string(i), Rancho);
        text.setCharacterSize(40);
        text.setPosition((floor->roomList[i].getPosX() + 8) * 100 - 10, (floor->roomList[i].getPosY() + 4.5) * 100 - 30);
        text.setFillColor(sf::Color::Black);
        roomTextNumbers.emplace_back(text);

        // highlight start and end room
        startPointer.setRadius(5);
        startPointer.setPosition((floor->roomList[floor->indexStartRoom].getPosX() + 8) * 100 - 30, (floor->roomList[floor->indexStartRoom].getPosY() + 4.5) * 100 - 30);
        startPointer.setFillColor(sf::Color::Green);

        endPointer.setRadius(5);
        endPointer.setPosition((floor->roomList[floor->indexEndRoom].getPosX() + 8) * 100 - 30, (floor->roomList[floor->indexEndRoom].getPosY() + 4.5) * 100 - 30);
        endPointer.setFillColor(sf::Color::Red);
    }

    //creation of the event
    sf::Event event;

    // Game loop
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            // closing the window and ending the game
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
            }
        }

        // TODO Updating the Game

        // Clearing the old frame and preparing for drawing the new onr
        window.clear(sf::Color::White);


        for (int i = 0; i < size(roomShapes); i++)
            window.draw(roomShapes[i]);
        for (int i = 0; i < size(roomTextNumbers); i++)
            window.draw(roomTextNumbers[i]);

        // Drawing all the objects of the game
        window.draw(startPointer); // TODO change once created the game class
        window.draw(endPointer);

        // Bring to screen and display the new frame just drawn
        window.display();
    }

    // End of the Game
    return 0;
}