//
// Created by longo on 19/07/2022.
//

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Collider.h"
#include "Game.h"

Collider::Collider(sf::Vector2f pos, sf::Vector2f dimensions, float angle) : angle(angle), isColliding(false) {
    this->pos = {pos.x * Game::getInstance()->getWidth(), pos.y * Game::getInstance()->getHeight()};
    this->dimensions = {dimensions.x * Game::getInstance()->getUnit(), dimensions.y * Game::getInstance()->getUnit()};

    colliderBox = sf::RectangleShape(sf::Vector2f(this->dimensions.x, this->dimensions.y));
    colliderBox.setOrigin(this->dimensions.x / 2, this->dimensions.y / 2);
    colliderBox.setOutlineThickness(3);
    colliderBox.setFillColor(sf::Color::Transparent);

    // define vertexes
    loadVertexes();
}

void Collider::loadVertexes() {
    vertexes = {};

    vertexes.emplace_back(dimensions.x / 2, -dimensions.y / 2);
    vertexes.emplace_back(dimensions.x / 2, dimensions.y / 2);
    vertexes.emplace_back(-dimensions.x / 2, dimensions.y / 2);
    vertexes.emplace_back(-dimensions.x / 2, -dimensions.y / 2);

    sf::Vector2f temp {};
    for (int i = 0; i < size(vertexes); i++) {
        temp.x = pos.x + vertexes[i].x * cosf(angle) - vertexes[i].y * sinf(angle);
        temp.y = pos.y + vertexes[i].x * sinf(angle) + vertexes[i].y * cosf(angle);
        vertexes[i].x = temp.x;
        vertexes[i].y = temp.y;
    }

    vertexPoints = {};
    for (int i = 0; i < size(vertexes); i++) {
        sf::CircleShape pt;
        pt.setRadius(3);
        pt.setOrigin(3, 3);
        pt.setPosition(vertexes[i].x, vertexes[i].y);
        pt.setFillColor(sf::Color::Blue);
        vertexPoints.emplace_back(pt);
    }
}

bool Collider::isCollidingWith(Collider other) {
    // assuming that it's colliding
    other.isColliding = true;

    sf::Vector2f minOverlappingAxis;
    float minOverlappingDepth = 9999;

    sf::Vector2f axis;
    float minA, maxA, minB, maxB;
    std::vector<float> projA {};
    std::vector<float> projB {};

    float overlappingDepth, axisMag;

    // for every vertex in this collider
    for (int i = 0; i < size(vertexes); i++) {
        // calculate the correspondent axis: the vector that connect two consecutive vertexes
        axis = {vertexes[(i + 1) % size(vertexes)].x - vertexes[i].x,
                vertexes[(i + 1) % size(vertexes)].y - vertexes[i].y};
        axisMag = sqrtf(powf(axis.x, 2) + powf(axis.y, 2));
        axis = {-axis.y / axisMag, axis.x / axisMag};

        // for every vertex of the first collider
        projA = {};
        for (int j = 0; j < size(vertexes); j++)
            // calculate its projection on the axis
            projA.emplace_back(vertexes[j].x * axis.x + vertexes[j].y * axis.y);

        // and find the min and the max proj values
        minA = *min_element(projA.begin(), projA.end());
        maxA = *max_element(projA.begin(), projA.end());

        // for every vertex of the second collider
        projB = {};
        for (int j = 0; j < size(other.vertexes); j++)
            // calculate its projection on the axis
            projB.emplace_back(other.vertexes[j].x * axis.x + other.vertexes[j].y * axis.y);

        // and find the min and the max proj values
        minB = *min_element(projB.begin(), projB.end());
        maxB = *max_element(projB.begin(), projB.end());

        // then compare min and max values
        if (minA > maxB || minB > maxA) {
            other.isColliding = false;
            return false;
        }

        // if they overlap, calculate the overlapping value
        overlappingDepth = std::min(maxA, maxB) - std::max(minA, minB);
        if (overlappingDepth < minOverlappingDepth) {
            minOverlappingDepth = overlappingDepth;
            minOverlappingAxis = axis;
        }
    }

    // for every vertex in the other collider
    for (int i = 0; i < size(other.vertexes); i++) {
        // calculate the correspondent axis: the vector that connect two consecutive vertexes
        axis = {other.vertexes[(i + 1) % size(other.vertexes)].x - other.vertexes[i].x,
                other.vertexes[(i + 1) % size(other.vertexes)].y - other.vertexes[i].y};
        axisMag = sqrtf(powf(axis.x, 2) + powf(axis.y, 2));
        axis = {-axis.y / axisMag, axis.x / axisMag};

        // for every vertex of the first collider
        projA = {};
        for (int j = 0; j < size(vertexes); j++)
            // calculate its projection on the axis
            projA.emplace_back(vertexes[j].x * axis.x + vertexes[j].y * axis.y);

        // and find the min and the max proj values
        minA = *min_element(projA.begin(), projA.end());
        maxA = *max_element(projA.begin(), projA.end());

        // for every vertex of the second collider
        projB = {};
        for (int j = 0; j < size(other.vertexes); j++)
            // calculate its projection on the axis
            projB.emplace_back(other.vertexes[j].x * axis.x + other.vertexes[j].y * axis.y);

        // and find the min and the max proj values
        minB = *min_element(projB.begin(), projB.end());
        maxB = *max_element(projB.begin(), projB.end());

        // then compare min and max values
        if (minA > maxB || minB > maxA) {
            other.isColliding = false;
            return false;
        }

        // if they overlap, calculate the overlapping value
        overlappingDepth = std::min(maxA, maxB) - std::max(minA, minB);
        if (overlappingDepth < minOverlappingDepth) {
            minOverlappingDepth = overlappingDepth;
            minOverlappingAxis = axis;
        }
    }

    // if this code is read, an overlap has been found
    isColliding = true;

    // check the right direction
    if (minOverlappingAxis.x * (other.pos.x - pos.x) + minOverlappingAxis.y * (other.pos.y - pos.y) <= 0)
        minOverlappingAxis = {-minOverlappingAxis.x, -minOverlappingAxis.y};

    // move the first collider back in position according to the overlapping value and axis
    float teta = atan2f(minOverlappingAxis.y, minOverlappingAxis.x);
    move(-minOverlappingDepth * cosf(teta), -minOverlappingDepth * sinf(teta));

    return true;
}

void Collider::move(float dx, float dy) {
    pos.x += dx;
    pos.y += dy;

    // recalculate all four vertexes
    loadVertexes();
}

void Collider::draw(sf::RenderWindow &window) {
    if (isColliding)
        colliderBox.setOutlineColor(sf::Color::Red);
    else
        colliderBox.setOutlineColor(sf::Color::Green);
    colliderBox.setPosition(pos.x, pos.y);
    colliderBox.setRotation(angle * 180 / M_PI);

    window.draw(colliderBox);

    // draw the vertexes
    for (int i = 0; i < size(vertexPoints); i++)
        window.draw(vertexPoints[i]);
}

bool Collider::isEqual(Collider other) {
    // TODO: make it a collider operator ==
    if (
        round(this->pos.x) == round(other.pos.x) &&
        round(this->pos.y) == round(other.pos.y) &&
        round(this->angle) == round(other.angle) &&
        round(this->dimensions.x) == round(other.dimensions.x) &&
        round(this->dimensions.y) == round(other.dimensions.y)
    )
        return true;
    else
        return false;
}