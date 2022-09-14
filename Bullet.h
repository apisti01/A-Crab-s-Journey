
//
// Created by apisti01 on 09/07/22.
//

#ifndef MAIN_CPP_BULLET_H
#define MAIN_CPP_BULLET_H

#include <SFML/Graphics.hpp>
#include "GameCharacter.h"

class FloorMap;

class Bullet {
public:
    // Constructor and Destructor
    Bullet(Collider* collider, sf::Texture* texture, float damage, float speed, bool isTracking, bool isShattering, GameCharacter* shooter);
    ~Bullet() = default;

    // getters and setters
    float getDamage() const { return damage; }
    void setDamage(float damage) { Bullet::damage = damage; }

    float getSpeed() const { return speed; }
    void setSpeed(float speed) { Bullet::speed = speed; }

    // move the bullet with his speed on its trajectory
    void update(int deltaTime);
    bool checkCollisions(FloorMap *floor);

    void draw(sf::RenderWindow& window);

private:
    float damage, speed;

    // directions chosen when launched
    sf::Vector2f pos, dimensions;
    float direction;

    // Special ability
    bool isTracking, isShattering;

    GameCharacter* shooter;

    Collider collider;

    // SFML Sprite
    sf::Texture texture;
    sf::Sprite sprite;
    float spriteScale;
};


#endif //MAIN_CPP_BULLET_H
