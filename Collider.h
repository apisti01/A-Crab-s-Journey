//
// Created by longo on 19/07/2022.
//

#ifndef ACRABSJOURNEY_COLLIDER_H
#define ACRABSJOURNEY_COLLIDER_H


class Collider {
public:
    Collider(float posX, float posY, float width, float height, float angle = 0) : posX(posX), posY(posY), width(width),
    height(height), angle(angle), isColliding(false) {};

    // getters and setters
    float getAngle() const {
        return angle;
    }
    void setAngle(float angle) {
        Collider::angle = angle;
    }

    float getPosX() const {
        return posX;
    }
    void setPosX(int posX) {
        Collider::posX = posX;
    }

    float getPosY() const {
        return posY;
    }
    void setPosY(int posY) {
        Collider::posY = posY;
    }

    float getWidth() const {
        return width;
    }
    void setWidth(int width) {
        Collider::width = width;
    }

    float getHeight() const {
        return height;
    }
    void setHeight(int height) {
        Collider::height = height;
    }

    void move(float dx, float dy);

    void draw(sf::RenderWindow &window);

    void isCollidingWith(Collider other);
    bool isColliding;

    sf::RectangleShape colliderBox;
protected:

private:
    float angle;
    float posX;
    float posY;
    float width;
    float height;
};


#endif //ACRABSJOURNEY_COLLIDER_H
