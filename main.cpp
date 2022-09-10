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
    cout << window.getSize().x << " x " << window.getSize().y << endl;

    // creation of the event
    sf::Event event;

    // create the game
    auto game = Game::getInstance();

    // determine the aspect ratio of the screen the game is been playing on
    game->getMeasures(window);

    bool clicked;

    // Game loop
    while (window.isOpen()) {
        int deltaTime = game->clock.restart().asMicroseconds();

        clicked = false;

        while (window.pollEvent(event)) {
            // closing the window and ending the game
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                        clicked = true;
            }
            // handles the event of the current state, like changing state or other actions
            game->eventHandling(event, window);
        }

        // Clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color::White);

        // game update and draw
        game->update(deltaTime, clicked, window);
        game->draw(window);

        // Bring to screen and display the new frame just drawn
        window.display();
    }

    // clean
    delete game;

    // End of the Game
    return 0;
}