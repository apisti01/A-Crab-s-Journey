//
// Created by longo on 19/07/2022.
//

#ifndef ACRABSJOURNEY_COLLIDER_H
#define ACRABSJOURNEY_COLLIDER_H

#include <cmath>

class Collider {
public:
    Collider() {};
    Collider(sf::Vector2f pos, sf::Vector2f dimensions, float angle = 0);

    // getters and setters
    float getAngle() const { return angle; }
    void setAngle(float angle) {
        Collider::angle = angle;
        while (Collider::angle <= -M_PI || Collider::angle > M_PI)
            Collider::angle -= fabs(Collider::angle) / Collider::angle * 2 * M_PI;
    }

    sf::Vector2f getPosition() const { return pos; }
    void setPosition(sf::Vector2f pos) { Collider::pos = pos; }
    float getPosX() const { return pos.x; }
    void setPosX(float posX) { Collider::pos.x = posX; }
    float getPosY() const { return pos.y; }
    void setPosY(float posY) { Collider::pos.y = posY; }

    sf::Vector2f getPrevPosition() const { return prevPos; }
    void setPrevPosition(sf::Vector2f prevPos) { Collider::prevPos = prevPos; }
    float getPrevPosX() const { return prevPos.x; }
    void setPrevPosX(int prevPosX) { Collider::prevPos.x = prevPosX; }
    float getPrevPosY() const { return prevPos.y; }
    void setPrevPosY(int prevPosY) { Collider::prevPos.y = prevPosY; }

    sf::Vector2f getDimensions() const { return dimensions; }
    void setDimensions(sf::Vector2f dimensions) { Collider::dimensions = dimensions; }
    float getWidth() const { return dimensions.x; }
    void setWidth(int width) { Collider::dimensions.x = width; }
    float getHeight() const { return dimensions.y; }
    void setHeight(int height) { Collider::dimensions.y = height; }

    void move(float dx, float dy);

    void draw(sf::RenderWindow &window);

    bool isEqual(const Collider& other) const;

    bool isCollidingWith(Collider other);

    bool isColliding;

    sf::RectangleShape colliderBox;

private:
    sf::Vector2f pos, prevPos;
    sf::Vector2f dimensions;
    float angle;

    void loadVertexes();

    std::vector<sf::Vector2f> vertexes;
    std::vector<sf::CircleShape> vertexPoints;
};


#endif //ACRABSJOURNEY_COLLIDER_H
