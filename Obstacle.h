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
    explicit Obstacle(const sf::Texture &texture, Collider collider, float posX, float posY, float width, float height, float damage = 0) :
    texture(texture), collider(collider), posX(posX), posY(posY), width(width), height(height), damage(damage) {
        flip = 2 * (rand() % 2) - 1;
    };

    float getPosX() const { return posX; }
    void setPosX(int posX) { Obstacle::posX = posX; }

    float getPosY() const { return posY; }
    void setPosY(int posY) { Obstacle::posY = posY; }

    float getWidth() const { return width; }
    void setWidth(int width) { Obstacle::width = width; }

    float getHeight() const { return height; }
    void setHeight(int height) { Obstacle::height = height; }

    float getDamage() const { return damage; }
    void setDamage(float damage) { Obstacle::damage = damage; }

    // collider
    Collider collider;

    void draw(sf::RenderWindow &window);

private:
    // info about position and dimensions
    float posX, posY;
    float width, height;
    int flip;

    // damage
    float damage;

    // sprite and texture
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif //ACRABSJOURNEY_OBSTACLE_H
