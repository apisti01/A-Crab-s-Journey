//
// Created by apisti01 on 20/07/22.
//

#include "StateMainMenu.h"
StateMainMenu::StateMainMenu(Game *game) : State(game) {
    backgroundTexture.loadFromFile("../Games_States/Start_Menu/Start_Menu.png");
}

void StateMainMenu::eventHandling(sf::Event event) {

}

void StateMainMenu::draw(sf::RenderWindow &window) {
    window.draw(background);
}
