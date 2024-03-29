//
// Created by apisti01 on 20/07/22.
//

#include "StateTitleScreen.h"
#include <string>

StateTitleScreen::StateTitleScreen(Game* game): State(game) {
    background.rect.setSize({game->getWidth(), game->getHeight()});
    background.rect.setOrigin({game->getWidth() / 2, game->getHeight() / 2});
}

void StateTitleScreen::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    titleText.update(window);
    pressBtnText.update(window);

    copyright.update(window);
    copyright.text.setFillColor(sf::Color(255, 255, 255, 192));
    string copyrightString = "";
    copyrightString.append(1, 0xA9);
    copyrightString.append("2022 I'TEAM, ALL RIGHTS RESERVED.");
    copyright.text.setString(copyrightString);

    timer += deltaTime / pow(10, 6);
    int opacity = 192 + 64 * sinf(4 * timer);
    pressBtnText.text.setFillColor(sf::Color(255, 255, 255, opacity));
}

void StateTitleScreen::eventHandling(sf::Event event, sf::RenderWindow &window) {
    // when clicked any key it changes and go to the Start/Main menu
    if (event.type == sf::Event::KeyReleased || event.type == sf::Event::MouseButtonReleased)
        game->changeState(StateType::MainMenu);
}

void StateTitleScreen::draw(sf::RenderWindow &window) {
    background.draw(window);

    titleText.draw(window);
    pressBtnText.draw(window);

    copyright.draw(window);
}
