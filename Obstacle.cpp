//
// Created by longo on 07/07/2022.
//

#include "Obstacle.h"

void Obstacle::draw(sf::RenderWindow &window) {
    sprite = sf::Sprite(texture, sf::IntRect(0, 0, 240, 240));
    sprite.setOrigin(120, 120);
    sprite.setPosition(posX, posY);

    window.draw(sprite);

    collider.draw(window);
}