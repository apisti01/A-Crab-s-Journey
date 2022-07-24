//
// Created by longo on 19/07/2022.
//

#ifndef ACRABSJOURNEY_COLLIDER_H
#define ACRABSJOURNEY_COLLIDER_H


class Collider {
public:
    Collider() {};
    Collider(float posX, float posY, float width, float height, float angle = 0)
    : posX(posX), posY(posY), width(width), height(height), angle(angle), isColliding(false) {
        colliderBox = sf::RectangleShape(sf::Vector2f(width, height));
        colliderBox.setOrigin(width / 2, height / 2);
        colliderBox.setOutlineThickness(3);
        colliderBox.setFillColor(sf::Color::Transparent);
    };

    // getters and setters
    float getAngle() const { return angle; }
    void setAngle(float angle) { Collider::angle = angle; }

    float getPosX() const { return posX; }
    void setPosX(float posX) { Collider::posX = posX; }

    float getPosY() const { return posY; }
    void setPosY(float posY) { Collider::posY = posY; }

    float getWidth() const { return width; }
    void setWidth(int width) { Collider::width = width; }

    float getHeight() const { return height; }
    void setHeight(int height) { Collider::height = height; }

    void move(float dx, float dy);

    void draw(sf::RenderWindow &window);

    void isCollidingWith(Collider other);
    bool isColliding;

    sf::RectangleShape colliderBox;

private:
    float posX, posY;
    float width, height;
    float angle;
};


#endif //ACRABSJOURNEY_COLLIDER_H
