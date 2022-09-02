//
// Created by longo on 02/09/2022.
//

#include "TextButton.h"

TextButton::TextButton(std::string string, sf::Font &font, int characterSize, sf::Vector2f position, bool clickable, std::string origin) : clickable(clickable), origin(origin) {
    text.setString(string);
    text.setCharacterSize(characterSize);
    text.setPosition(position);
    text.setFont(font);
}

void TextButton::update(sf::RenderWindow &window) {
    if (clickable) {
        if (text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            text.setFillColor(sf::Color::White);
        else
            text.setFillColor(sf::Color(255, 255, 255, 128));
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
