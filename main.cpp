#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>
#include "ctime"

#include "FloorMap.h"
#include "FloorMap.cpp"
#include "Player.h"
#include "MeleeWeapon.h"

int main() {
    // caricamento del font
    sf::Font Rancho;
    if (!Rancho.loadFromFile("../Font/Arial/Arial.ttf")) {
        cout << "font non caricato" << endl;
        system("pause");
    }

    srand(time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "A Crab's Journey");

    /*
    // load and set Game's Icon
    sf::Image icon;
    icon.loadFromFile("../Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    int level = 20;
    std::vector<sf::RectangleShape> roomShapes;
    std::vector<sf::Text> roomTextNumbers;
    sf::CircleShape startPointer, endPointer, shopPointer;

    // TODO: setup the game
    Player player = new Player();

    // create new floor
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
    }

    // highlight start, end and shop room
    startPointer.setRadius(10);
    startPointer.setPosition((floor->roomList[floor->startRoomIndex].getPosX() + 8) * 100 - 35, (floor->roomList[floor->startRoomIndex].getPosY() + 4.5) * 100 - 35);
    startPointer.setFillColor(sf::Color::Green);

    endPointer.setRadius(10);
    endPointer.setPosition((floor->roomList[floor->endRoomIndex].getPosX() + 8) * 100 - 35, (floor->roomList[floor->endRoomIndex].getPosY() + 4.5) * 100 - 35);
    endPointer.setFillColor(sf::Color::Red);

    shopPointer.setRadius(10);
    shopPointer.setPosition((floor->roomList[floor->shopRoomIndex].getPosX() + 8) * 100 + 15, (floor->roomList[floor->shopRoomIndex].getPosY() + 4.5) * 100 - 35);
    shopPointer.setFillColor(sf::Color::Blue);
    */

    // the following are instance to test the movement
    sf::Texture brownCrab;
    brownCrab.loadFromFile("../Textures/Brown_Crab_texture.png");

    std::unique_ptr<Weapon> weapon = std::make_unique<MeleeWeapon>(10, "carlo", ItemRarity::Common, 50);

    auto carlo = make_unique<Player>(brownCrab, std::move(weapon), CrabSpecie::BrownCrab, "jose", 10, 10, 5);

    carlo->setPosition(window.getSize().x / 2, window.getSize().y / 2);

    std::list<std::unique_ptr<Enemy>> enemyList {};

    //creation of the event
    sf::Event event;

    sf::Clock clockMain;

    // Game loop
    while (window.isOpen())
    {
        int  deltaTime = clockMain.restart().asMilliseconds();

        while (window.pollEvent(event)) {
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

        carlo->update(deltaTime, enemyList);

        // Clearing the old frame and preparing for drawing the new onr
        window.clear(sf::Color::White);

        carlo->draw(window);

        /*
        for (int i = 0; i < size(roomShapes); i++)
            window.draw(roomShapes[i]);
        for (int i = 0; i < size(roomTextNumbers); i++)
            window.draw(roomTextNumbers[i]);

        // Drawing all the objects of the game
        window.draw(startPointer); // TODO change once created the game class
        window.draw(endPointer);
        window.draw(shopPointer);
        */

        // Bring to screen and display the new frame just drawn
        window.display();
    }

    // End of the Game
    return 0;
}