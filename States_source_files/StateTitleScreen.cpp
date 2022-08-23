//
// Created by apisti01 on 20/07/22.
//

#include "StateTitleScreen.h"
#include "../Game.h"

StateTitleScreen::StateTitleScreen(Game* game): State(game) {
    backgroundTexture.loadFromFile("Games States/Start Menu/Start Menu Blank.png");

    titleBtnTexture.loadFromFile("Games States/Start Menu/A Crab's Journey Texture.png");
    float titleBtnScl = 1.3;
    titleBtn.setPosition(1920 / 2, 1080 / 2);
    titleBtn.setScale(titleBtnScl, titleBtnScl);
    titleBtn.setOrigin(titleBtnTexture.getSize().x / 2, titleBtnTexture.getSize().y / 2);
    titleBtn.setSize(sf::Vector2f(titleBtnTexture.getSize().x, titleBtnTexture.getSize().y));
    titleBtn.setTexture(&titleBtnTexture);
}

void StateTitleScreen::eventHandling(sf::Event event, sf::RenderWindow &window) {
    // when clicked any key it changes and go to the Start/Main menu
    if (event.type == sf::Event::KeyReleased) {
        game->changeState(StateType::MainMenu);
    }
}

void StateTitleScreen::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(titleBtn);
}
