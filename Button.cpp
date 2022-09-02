//
// Created by longo on 28/08/2022.
//

#include "Button.h"

Button::Button() {}

Button::Button(std::string texturePath, float scl, sf::Vector2f position, bool clickable) : clickable(clickable) {
    texture.loadFromFile(texturePath);
    box.setTexture(&texture);
    box.setPosition(position);
    box.setScale(scl, scl);
    box.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    box.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
}

Button::Button(std::string string, sf::Font &font, int characterSize, sf::Vector2f position, bool clickable, std::string origin) : clickable(clickable), origin(origin) {
    btnText.setString(string);
    btnText.setCharacterSize(characterSize);
    btnText.setPosition(position);
    btnText.setFont(font);
}

void Button::updateBtn(sf::RenderWindow &window) {
    if (clickable) {
        if (box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            box.setFillColor(sf::Color::White);
        else
            box.setFillColor(sf::Color(255, 255, 255, 128));

        if (btnText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            btnText.setFillColor(sf::Color::White);
        else
            btnText.setFillColor(sf::Color(255, 255, 255, 128));
    }

    // set the origin
    if (origin == "center")
        btnText.setOrigin(btnText.getLocalBounds().width / 2, btnText.getLocalBounds().height / 2);
    else if (origin == "topLeft")
        btnText.setOrigin(0, 0);
    else if (origin == "topRight")
        btnText.setOrigin(btnText.getLocalBounds().width, 0);
    else if (origin == "bottomLeft")
        btnText.setOrigin(0, btnText.getLocalBounds().height);
    else if (origin == "bottomRight")
        btnText.setOrigin(btnText.getLocalBounds().width, btnText.getLocalBounds().height);
}

void Button::drawBtn(sf::RenderWindow &window) const {
    window.draw(box);
}

void Button::drawTextBtn(sf::RenderWindow &window) const {
    window.draw(btnText);
}
