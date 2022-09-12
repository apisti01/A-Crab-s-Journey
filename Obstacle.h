//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_OBSTACLE_H
#define ACRABSJOURNEY_OBSTACLE_H

#include <memory>
#include <utility>
#include <SFML/Graphics.hpp>

#include "Collider.h"

using namespace std;

class Obstacle {
public:
    explicit Obstacle(const sf::Texture &texture, Collider collider, float damage = 0);

    sf::Vector2f getPos() const { return pos; }
    void setPos(sf::Vector2f pos) { Obstacle::pos = pos; }
    float getPosX() const { return pos.x; }
    void setPosX(int posX) { Obstacle::pos.x = posX; }
    float getPosY() const { return pos.y; }
    void setPosY(int posY) { Obstacle::pos.y = posY; }

    sf::Vector2f getDimensions() const { return dimensions; }
    void setDimensions(sf::Vector2f dimensions) { Obstacle::dimensions = dimensions; }
    float getWidth() const { return dimensions.x; }
    void setWidth(int width) { Obstacle::dimensions.x = width; }
    float getHeight() const { return dimensions.y; }
    void setHeight(int height) { Obstacle::dimensions.y = height; }

    float getDamage() const { return damage; }
    void setDamage(float damage) { Obstacle::damage = damage; }

    // collider
    Collider collider;

    void draw(sf::RenderWindow &window);

private:
    // info about position and dimensions
    sf::Vector2f pos;
    sf::Vector2f dimensions;
    int flip;

    // damage
    float damage;

    // sprite and texture
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif //ACRABSJOURNEY_OBSTACLE_H
