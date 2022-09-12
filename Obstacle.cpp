//
// Created by longo on 07/07/2022.
//

#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle(const sf::Texture &texture, Collider collider, float damage) : texture(texture), collider(collider), damage(damage) {
    pos = {collider.getPosX(), collider.getPosY()};
    dimensions = {collider.getWidth() * Game::getInstance()->getUnit() / texture.getSize().x,
                  collider.getHeight() * Game::getInstance()->getUnit() / texture.getSize().y};
    flip = 2 * (rand() % 2) - 1;
}

void Obstacle::draw(sf::RenderWindow &window) {
    sprite = sf::Sprite(texture, sf::IntRect(0, 0, 240, 240));
    sprite.setOrigin(120, 120);
    sprite.setPosition(pos);
    sprite.setScale(flip, 1);
    sprite.setScale(Game::getInstance()->getRatio(), Game::getInstance()->getRatio());

    window.draw(sprite);

    collider.draw(window);
}