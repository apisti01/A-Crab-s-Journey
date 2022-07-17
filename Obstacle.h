//
// Created by longo on 07/07/2022.
//

#ifndef ACRABSJOURNEY_OBSTACLE_H
#define ACRABSJOURNEY_OBSTACLE_H

#include <memory>

using namespace std;

class Obstacle {
public:
    explicit Obstacle(int posX, int posY, int width, int height) : posX(posX), posY(posY), width(width), height(height), damage(damage = 0) {};

    int getPosX() const {
        return posX;
    }
    void setPosX(int posX) {
        Obstacle::posX = posX;
    }

    int getPosY() const {
        return posY;
    }
    void setPosY(int posY) {
        Obstacle::posY = posY;
    }

    int getWidth() const {
        return width;
    }
    void setWidth(int width) {
        Obstacle::width = width;
    }

    int getHeight() const {
        return height;
    }
    void setHeight(int height) {
        Obstacle::height = height;
    }

    float getDamage() const {
        return damage;
    }
    void setDamage(float damage) {
        Obstacle::damage = damage;
    }

protected:

private:
    // info about position and dimensions
    int posX, posY;
    int width, height;

    // damage
    float damage;

    // sprite
    // std::unique_ptr<Sprite> sprite;
};

#endif //ACRABSJOURNEY_OBSTACLE_H
