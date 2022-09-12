//
// Created by longo on 02/09/2022.
//

#include "SpriteButton.h"
#include "Game.h"

SpriteButton::SpriteButton(std::string texturePath, float scl, sf::Vector2f position, bool clickable, std::string origin) : clickable(clickable), origin(origin) {
    texture.loadFromFile(texturePath);
    rect.setTexture(&texture);
    rect.setPosition({position.x * Game::getInstance()->getWidth(), position.y * Game::getInstance()->getHeight()});
    rect.setScale(scl * Game::getInstance()->getRatio(), scl * Game::getInstance()->getRatio());
    rect.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    rect.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
}

SpriteButton::SpriteButton(sf::Texture &texture, float scl, sf::Vector2f position, bool clickable, std::string origin)  : clickable(clickable), origin(origin) {
    this->texture = texture;
    rect.setTexture(&texture);
    rect.setPosition({position.x * Game::getInstance()->getWidth(), position.y * Game::getInstance()->getHeight()});
    rect.setScale(scl * Game::getInstance()->getRatio(), scl * Game::getInstance()->getRatio());
    rect.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    rect.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
}

void SpriteButton::update(sf::RenderWindow &window) {
    if (clickable) {
        if (rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            rect.setFillColor(sf::Color::White);
        else
            rect.setFillColor(sf::Color(255, 255, 255, 128));
    }

    // set the origin
    if (origin == "center") {
        rect.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    } else if (origin == "topLeft")
        rect.setOrigin(0, 0);
    else if (origin == "topRight")
        rect.setOrigin(texture.getSize().x, 0);
    else if (origin == "bottomLeft")
        rect.setOrigin(0, texture.getSize().y);
    else if (origin == "bottomRight")
        rect.setOrigin(texture.getSize().x, texture.getSize().y);
}

void SpriteButton::draw(sf::RenderWindow &window) {
    window.draw(rect);
}