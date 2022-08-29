//
// Created by apisti01 on 20/07/22.
//

#include "StateTitleScreen.h"

#include <iostream>

StateTitleScreen::StateTitleScreen(Game* game): State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");

    titleTxt.setString("A Crab's Journey");
    titleTxt.setCharacterSize(240);
    titleTxt.setFont(game->font);
    titleTxt.setPosition(1920 / 2, 1080 / 2);
}

void StateTitleScreen::eventHandling(sf::Event event, sf::RenderWindow &window) {
    // when clicked any key it changes and go to the Start/Main menu
    if (event.type == sf::Event::KeyReleased)
        game->changeState(StateType::MainMenu);
}

void StateTitleScreen::draw(sf::RenderWindow &window) {
    window.draw(background);

    titleTxt.setOrigin(titleTxt.getLocalBounds().width / 2, titleTxt.getLocalBounds().height / 2);
    window.draw(titleTxt);
}
