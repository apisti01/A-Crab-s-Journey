
//
// Created by apisti01 on 09/07/22.
//

#ifndef MAIN_CPP_BULLET_H
#define MAIN_CPP_BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    // Constructor and Destructor
    Bullet(float damage, float speed, float range, const sf::Sprite &sprite, sf::Vector2f playerPosition,
           sf::Vector2f directions, bool isTracking, bool isShattering);
    ~Bullet() = default;

    // getters and setters
    float getDamage() const { return damage; }
    void setDamage(float damage) { Bullet::damage = damage; }

    float getRange() const { return range; }
    void setRange(float range) { Bullet::range = range; }

    float getSpeed() const { return speed; }
    void setSpeed(float speed) { Bullet::speed = speed; }

    // move the bullet with his speed on its trajectory
    void move(int deltaTime);

    void draw(sf::RenderWindow& window);

private:
    float damage;
    float range;
    float speed;

    // directions chosen when launched
    sf::Vector2f directions;

    // Special ability
    bool isTracking;
    bool isShattering;

    // SFML Sprite
    sf::Sprite sprite;
};


#endif //MAIN_CPP_BULLET_H
