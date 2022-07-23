#include <SFML/Graphics.hpp>

#include <memory>
#include <ctime>
#include <iostream>

#include "FloorMap.h"
#include "Player.h"
#include "MeleeWeapon.h"
#include "RangedWeapon.h"
#include "Game.h"

int main() {

    // initialize the randomic generation
    srand(time(nullptr));

    // font load
    sf::Font Rancho;
    if (!Rancho.loadFromFile("../Font/Arial/Arial.ttf")) {
        cout << "font non caricato" << endl;
        system("pause");
    }

    // load window
    sf::RenderWindow window(sf::VideoMode(), "A Crab's Journey", sf::Style::Fullscreen);

    /*
    // load and set Game's Icon
    sf::Image icon;
    icon.loadFromFile("../Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
     */

    // load coral reef texture as room background
    sf::Texture coralReef;
    coralReef.loadFromFile("../Map/Coral Reef/Coral Reef.png");
    sf::Sprite backgroundSprite(coralReef, sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    int level = 1;
    std::vector<sf::RectangleShape> roomShapes;
    std::vector<sf::Text> roomTextNumbers;
    sf::CircleShape startPointer, endPointer, shopPointer, currentPointer;

    // create new floor
    FloorMap *floor = new FloorMap(level, window.getSize().x, window.getSize().y);

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
    shopPointer.setFillColor(sf::Color::Yellow);

    currentPointer.setRadius(10);
    currentPointer.setFillColor(sf::Color::Blue);

    // load brown crab's texture for movement animation
    sf::Texture brownCrabTexture;
    brownCrabTexture.loadFromFile("../GameCharacter/Player/Brown Crab/Animations/Texture.png");

    // bullet for ranged weapon
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("../others/bullet_rock.png");
    sf::Sprite bullet {bulletTexture};
    bullet.setScale(0.02,0.02);

    // Ranged weapon
    std::unique_ptr<Weapon> rangedWeapon = std::make_unique<RangedWeapon>(bullet);

    // give him a melee weapon
    std::unique_ptr<Weapon> weapon = std::make_unique<MeleeWeapon>(10, "player", ItemRarity::Common, 50);
    // and a collider
    Collider collider(window.getSize().x / 2, window.getSize().y / 2,
                      brownCrabTexture.getSize().x / 6 * 0.4 * 0.6,
                      brownCrabTexture.getSize().y / 3 * 0.4 * 0.8, 0);
    // create the player
    auto player = make_unique<Player>("Crab", CrabSpecie::BrownCrab, brownCrabTexture, collider, std::move(rangedWeapon), 10, 10, 1, 1, 10, 10, 10, 10);
    // and set his position at the center of the map
    player->setPosition(window.getSize().x / 2, window.getSize().y / 2);

    // create an enemy list
    std::list<std::unique_ptr<Enemy>> enemyList {};

    // creation of the event
    sf::Event event;

    sf::Clock clockMain;

    // finally let's create the game
    auto game = Game::getInstance();

    // Game loop
    while (window.isOpen())
    {
        int deltaTime = clockMain.restart().asMicroseconds(); // TODO remove once we use the gameclock

        while (window.pollEvent(event)) {
            // closing the window and ending the game
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
            }
            // handles the event of the current state, like changing state or other actions
            game->eventHandling(event);
        }

        // if M key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
            // reset canvas
            window.clear(sf::Color::White);

            // and draw the map
            for (int i = 0; i < size(roomShapes); i++)
                window.draw(roomShapes[i]);
            for (int i = 0; i < size(roomTextNumbers); i++)
                window.draw(roomTextNumbers[i]);

            // Drawing all the objects of the game
            window.draw(startPointer);
            window.draw(endPointer);
            window.draw(shopPointer);
            window.draw(currentPointer);
        } else {
            // Clearing the old frame and preparing for drawing the new one
            window.clear(sf::Color::White);

            // draw the current room
            window.draw(backgroundSprite);
            floor->draw(window);

            // update and draw the player
            player->update(deltaTime, floor, enemyList);
            player->draw(window);

            currentPointer.setPosition((floor->roomList[floor->currentRoomIndex].getPosX() + 8) * 100 + 15, (floor->roomList[floor->currentRoomIndex].getPosY() + 4.5) * 100 + 15);

            // TODO Updating the rest of the game
        }

        //window.clear(sf::Color::Green);

        //game->update();

        //game->draw(window);

        // Bring to screen and display the new frame just drawn
        window.display();

        game->restartClock(); // TODO keep only this clock
    }

    // clean
    delete game;

    // End of the Game
    return 0;
}