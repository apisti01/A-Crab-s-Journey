//
// Created by longo on 02/09/2022.
//

#include "TextButton.h"
#include "Game.h"

TextButton::TextButton(std::string string, int characterSize, sf::Vector2f position, bool clickable, std::string origin) :
        characterSize(characterSize), minCharacterSize(characterSize), maxCharacterSize(characterSize + 30),
        clickable(clickable), origin(origin) {
    text.setString(string);
    text.setCharacterSize(characterSize * Game::getInstance()->getRatio());
    text.setPosition({position.x * Game::getInstance()->getWidth(), position.y * Game::getInstance()->getHeight()});
    text.setFont(Game::getInstance()->font);
}

void TextButton::update(sf::RenderWindow &window) {
    // check if mouse is on the text
    hovered = false;
    if (text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        hovered = true;

    // if it's clickable
    if (clickable) {
        // if the mouse is on the text
        if (hovered) {
            // set the text color to white
            text.setFillColor(sf::Color::White);
            // and increase the character size
            if (characterSize < maxCharacterSize)
                text.setCharacterSize(characterSize++);
        } else {
            // otherwise set the color to semitransparent
            text.setFillColor(sf::Color(255, 255, 255, 128));
            // and decrease the character size
            if (characterSize > minCharacterSize)
                text.setCharacterSize(characterSize--);
        }
    }

    // set the origin
    if (origin == "center") {
        text.setOrigin(text.getLocalBounds().width / 2 + text.getLocalBounds().left,
                       text.getLocalBounds().height / 2 + text.getLocalBounds().top);
    } else if (origin == "topLeft")
        text.setOrigin(text.getLocalBounds().left,
                       text.getLocalBounds().top);
    else if (origin == "topRight")
        text.setOrigin(text.getLocalBounds().width + text.getLocalBounds().left,
                       text.getLocalBounds().top);
    else if (origin == "bottomLeft")
        text.setOrigin(text.getLocalBounds().left,
                       text.getLocalBounds().height + text.getLocalBounds().top);
    else if (origin == "bottomRight")
        text.setOrigin(text.getLocalBounds().width + text.getLocalBounds().left,
                       text.getLocalBounds().height + text.getLocalBounds().top);
}

void TextButton::draw(sf::RenderWindow &window) {
    window.draw(text);
}
