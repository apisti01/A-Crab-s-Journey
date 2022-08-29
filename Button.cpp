//
// Created by longo on 28/08/2022.
//

#include "Button.h"

Button::Button(std::string texturePath, float scl, float posX, float posY, bool clickable) {
    btnTexture.loadFromFile(texturePath);
    btnBox.setTexture(&btnTexture);
    btnBox.setPosition(posX, posY);
    btnBox.setScale(scl, scl);
    btnBox.setOrigin(btnTexture.getSize().x / 2, btnTexture.getSize().y / 2);
    btnBox.setSize(sf::Vector2f(btnTexture.getSize().x, btnTexture.getSize().y));
    if (clickable)
        btnBox.setFillColor(sf::Color(255, 255, 255, 128));
}

void Button::updateBtn(sf::RenderWindow &window) {
    if (btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        btnBox.setFillColor(sf::Color(255, 255, 255, 255));
    else
        btnBox.setFillColor(sf::Color(255, 255, 255, 128));
}

void Button::drawBtn(sf::RenderWindow &window) {
    window.draw(btnBox);
}
