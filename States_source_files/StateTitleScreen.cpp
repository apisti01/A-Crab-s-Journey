//
// Created by apisti01 on 20/07/22.
//

#include "StateTitleScreen.h"

StateTitleScreen::StateTitleScreen(Game* game): State(game) {
    backgroundTexture.loadFromFile("Assets/GameStates/MainMenu/Background.png");
}

void StateTitleScreen::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    titleText.update(window);
    pressBtnText.update(window);

    timer += deltaTime / pow(10, 6);
    int opacity = 192 + 64 * sinf(4 * timer);
    pressBtnText.text.setFillColor(sf::Color(255, 255, 255, opacity));
}

void StateTitleScreen::eventHandling(sf::Event event, sf::RenderWindow &window) {
    // when clicked any key it changes and go to the Start/Main menu
    if (event.type == sf::Event::KeyReleased)
        game->changeState(StateType::MainMenu);
}

void StateTitleScreen::draw(sf::RenderWindow &window) {
    window.draw(background);

    titleText.draw(window);
    pressBtnText.draw(window);
}
