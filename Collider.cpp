//
// Created by longo on 19/07/2022.
//

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <bitset>
#include <list>

#include "Collider.h"


Collider::Collider(float posX, float posY, float width, float height, float angle) :
posX(posX), posY(posY), prevPosX(posX), prevPosY(posY), width(width), height(height), angle(angle), isColliding(false) {
    colliderBox = sf::RectangleShape(sf::Vector2f(width, height));
    colliderBox.setOrigin(width / 2, height / 2);
    colliderBox.setOutlineThickness(3);
    colliderBox.setFillColor(sf::Color::Transparent);

    // define all four vertexes
    vertexes = {
            { width / 2, -height / 2 },
            { width / 2, height / 2 },
            { -width / 2, height / 2 },
            { -width / 2, -height / 2 }
    };

    // rotate all vertexes by the angle
    sf::Vector2f temp {};
    for (int i = 0; i < size(vertexes); i++) {
        temp.x = posX + vertexes[i].x * cosf(angle) - vertexes[i].y * sinf(angle);
        temp.y = posY + vertexes[i].x * sinf(angle) + vertexes[i].y * cosf(angle);
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
};

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
    if (minOverlappingAxis.x * (other.posX - posX) + minOverlappingAxis.y * (other.posY - posY) <= 0)
        minOverlappingAxis = {-minOverlappingAxis.x, -minOverlappingAxis.y};

    // move the first collider back in position according to the overlapping value and axis
    float teta = atan2f(minOverlappingAxis.y, minOverlappingAxis.x);
    move(-minOverlappingDepth * cosf(teta), -minOverlappingDepth * sinf(teta));

    return true;
}

void Collider::move(float dx, float dy) {
    posX = posX + dx;
    posY = posY + dy;

    // define all four vertexes
    vertexes = {
            { width / 2, -height / 2 },
            { width / 2, height / 2 },
            { -width / 2, height / 2 },
            { -width / 2, -height / 2 }
    };

    sf::Vector2f temp {};
    for (int i = 0; i < size(vertexes); i++) {
        temp.x = posX + vertexes[i].x * cosf(angle) - vertexes[i].y * sinf(angle);
        temp.y = posY + vertexes[i].x * sinf(angle) + vertexes[i].y * cosf(angle);
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

void Collider::draw(sf::RenderWindow &window) {
    if (isColliding)
        colliderBox.setOutlineColor(sf::Color::Red);
    else
        colliderBox.setOutlineColor(sf::Color::Green);
    colliderBox.setPosition(posX, posY);
    colliderBox.setRotation(angle * 180 / M_PI);

    // window.draw(colliderBox);

    // draw the vertexes
    // for (int i = 0; i < size(vertexPoints); i++)
        // window.draw(vertexPoints[i]);
}

bool Collider::isEqual(Collider other) {
    // TODO: make it a collider operator ==
    if (
        this->posX == other.posX &&
        this->posY == other.posY &&
        this->angle == other.angle &&
        this->width == other.width &&
        this->height == other.height
    )
        return true;
    else
        return false;
}