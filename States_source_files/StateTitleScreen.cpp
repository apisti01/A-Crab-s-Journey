//
// Created by apisti01 on 20/07/22.
//

#include "StateTitleScreen.h"

#include <iostream>

StateTitleScreen::StateTitleScreen(Game* game): State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");
}

void StateTitleScreen::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    timer += deltaTime / pow(10, 6);
    int opacity = 192 + 64 * sinf(4 * timer);
    pressBtnText.btnText.setFillColor(sf::Color(255, 255, 255, opacity));
}

void StateTitleScreen::eventHandling(sf::Event event, sf::RenderWindow &window) {
    // when clicked any key it changes and go to the Start/Main menu
    if (event.type == sf::Event::KeyReleased)
        game->changeState(StateType::MainMenu);
}

void StateTitleScreen::draw(sf::RenderWindow &window) {
    window.draw(background);

    titleText.btnText.setOrigin(titleText.btnText.getLocalBounds().width / 2, titleText.btnText.getLocalBounds().height / 2);
    titleText.drawTextBtn(window);

    pressBtnText.btnText.setOrigin(pressBtnText.btnText.getLocalBounds().width / 2, pressBtnText.btnText.getLocalBounds().height / 2);
    pressBtnText.drawTextBtn(window);
}
