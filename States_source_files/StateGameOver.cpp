//
// Created by longo on 03/09/2022.
//

#include "StateGameOver.h"

StateGameOver::StateGameOver(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");
}

void StateGameOver::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (returnTextBtn.text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
            pearlsGained.text.getString() == to_string(p)) {
            // go to the main menu
            game->globalProgress.pearls += p;
            game->globalProgress.updateTxtFile();
            game->changeState(StateType::MainMenu);
        }
    }
}

void StateGameOver::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    titleText.update(window);
    returnTextBtn.update(window);

    if (t < s)
        t += deltaTime / pow(10, 6);

    // display the pearls gained with the run
    float a = -p / powf(s, 2);
    float b = 2 * p / s;
    pearlsGained.text.setString(to_string(int(round(a * powf(t, 2) + (b * t)))));
    pearlsGained.update(window);
    pearlsIcon.update(window);
}

void StateGameOver::draw(sf::RenderWindow &window) {
    window.draw(background);

    titleText.draw(window);

    pearlsGained.draw(window);
    pearlsIcon.draw(window);

    if (pearlsGained.text.getString() == to_string(p))
        returnTextBtn.draw(window);
}