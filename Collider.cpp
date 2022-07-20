//
// Created by longo on 19/07/2022.
//

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <bitset>

#include "Collider.h"

void Collider::isCollidingWith(Collider other) {
    // for every vertex of this collider
    for (int i = 0; i < 4; i++) {
        std::string x = std::bitset<2>(i).to_string();
        std::string y = std::bitset<2>((5 - i) % 4).to_string();

        sf::Vector2f pt(posX + pow(-1, x[0]) * width / 2 * cosf(angle) + pow(-1, x[1]) * height / 2 * sinf(angle),
                        posY + pow(-1, y[0]) * width / 2 * sinf(angle) + pow(-1, y[1]) * height / 2 * cosf(angle));
        float teta = abs(angle - atan2f(pt.y - other.posY, pt.x - other.posX));
        float dist = sqrtf(powf(pt.x - other.posX, 2) + powf(pt.y - other.posY, 2));

        // check if the vertex is in the other collider
        if (dist * cosf(teta) > -other.width / 2 && dist * cosf(teta) < other.width / 2 &&
            dist * sinf(teta) > -other.height / 2 && dist * sinf(teta) < other.height / 2) {
            isColliding = true;
            other.isColliding = true;
        }
    }

    // for every vertex of the other collider
    for (int i = 0; i < 4; i++) {
        std::string x = std::bitset<2>(i).to_string();
        std::string y = std::bitset<2>((5 - i) % 4).to_string();

        sf::Vector2f pt(other.posX + pow(-1, x[0]) * other.width / 2 * cosf(other.angle) +
                        pow(-1, x[1]) * other.height / 2 * sinf(other.angle),
                        other.posY + pow(-1, y[0]) * other.width / 2 * sinf(other.angle) +
                        pow(-1, y[1]) * other.height / 2 * cosf(other.angle));
        float teta = abs(other.angle - atan2f(pt.y - posY, pt.x - posX));
        float dist = sqrtf(powf(pt.x - posX, 2) + powf(pt.y - posY, 2));

        // check if the vertex is in the other collider
        if (dist * cosf(teta) > -width / 2 && dist * cosf(teta) < width / 2 &&
            dist * sinf(teta) > -height / 2 && dist * sinf(teta) < height / 2) {
            isColliding = true;
            other.isColliding = true;
        }
    }
}

void Collider::move(float dx, float dy) {
    posX = posX + dx;
    posY = posY + dy;
}

void Collider::draw(sf::RenderWindow &window) {
    colliderBox = sf::RectangleShape(sf::Vector2f(width, height));
    colliderBox.setOrigin(width / 2, height / 2);
    if (isColliding)
        colliderBox.setOutlineColor(sf::Color::Red);
    else
        colliderBox.setOutlineColor(sf::Color::Green);
    colliderBox.setOutlineThickness(3);
    colliderBox.setFillColor(sf::Color::Transparent);
    colliderBox.setPosition(posX, posY);
    colliderBox.setRotation(angle * 180 / M_PI);

    window.draw(colliderBox);
}
