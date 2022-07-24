#include <SFML/Graphics.hpp>

#include <memory>
#include <ctime>
#include <iostream>

#include "FloorMap.h"
#include "Game.h"

int main() {
    // initialize the randomic number generator
    srand(time(nullptr));

    // load window
    sf::RenderWindow window(sf::VideoMode(), "A Crab's Journey", sf::Style::Fullscreen);

    // load and set Game's Icon
    sf::Image icon;
    icon.loadFromFile("../Icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // creation of the event
    sf::Event event;

    // create the game
    auto game = Game::getInstance();

    // Game loop
    while (window.isOpen()) {
        int deltaTime = game->clock.restart().asMicroseconds();

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

        // Clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color::White);

        // game update and draw
        game->update(deltaTime);
        game->draw(window);

        // Bring to screen and display the new frame just drawn
        window.display();
    }

    // clean
    delete game;

    // End of the Game
    return 0;
}