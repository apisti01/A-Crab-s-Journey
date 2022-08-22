//
// Created by longo on 19/07/2022.
//

#ifndef ACRABSJOURNEY_COLLIDER_H
#define ACRABSJOURNEY_COLLIDER_H


#include <cmath>

class Collider {
public:
    Collider() {};
    Collider(float posX, float posY, float width, float height, float angle = 0);

    // getters and setters
    float getAngle() const { return angle; }
    void setAngle(float angle) {
        Collider::angle = angle;
        while (Collider::angle <= -M_PI || Collider::angle > M_PI)
            Collider::angle -= fabs(Collider::angle) / Collider::angle * 2 * M_PI;
    }

    float getPosX() const { return posX; }
    void setPosX(float posX) { Collider::posX = posX; }

    float getPosY() const { return posY; }
    void setPosY(float posY) { Collider::posY = posY; }

    float getPrevPosX() const { return prevPosX; }
    void setPrevPosX(float prevPosX) { Collider::prevPosX = prevPosX; }

    float getPrevPosY() const { return prevPosY; }
    void setPrevPosY(float prevPosY) { Collider::prevPosY = prevPosY; }

    float getWidth() const { return width; }
    void setWidth(int width) { Collider::width = width; }

    float getHeight() const { return height; }
    void setHeight(int height) { Collider::height = height; }

    void move(float dx, float dy);

    void draw(sf::RenderWindow &window);

    bool isEqual(Collider other);

    bool isCollidingWith(Collider other);

    bool isColliding;

    sf::RectangleShape colliderBox;

private:
    float posX, posY;
    float prevPosX, prevPosY;
    float width, height;
    float angle;

    std::vector<sf::Vector2f> vertexes{};
    std::vector<sf::CircleShape> vertexPoints{};
};


#endif //ACRABSJOURNEY_COLLIDER_H
