//
// Created by apisti01 on 20/07/22.
//

#include "StateTitleScreen.h"
#include "Game.h"

void StateTitleScreen::eventHandling(sf::Event event) {
    // when clicked any key it changes and go to the Start/Main menu
    if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonPressed){
        game->changeState(StateType::MainMenu);
    }
}

void StateTitleScreen::draw(sf::RenderWindow &window) {
    window.draw(background);
}

StateTitleScreen::StateTitleScreen(Game* game): State(game) {
    backgroundTexture.loadFromFile("../Games_States/TitleScreen/Title_Screen.png");
}
