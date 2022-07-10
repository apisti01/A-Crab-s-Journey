
//
// Created by apisti01 on 09/07/22.
//

#ifndef MAIN_CPP_BULLET_H
#define MAIN_CPP_BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    // Constructor and Destructor
    Bullet(float damage, float speed, float range, sf::Sprite body, bool isTracking, bool isShattering);
    ~Bullet() = default;

private:

    float damage;
    float range;
    float speed;

    // Special ability
    bool isTracking;
    bool isShattering;

    // SFML Sprite
    sf::Sprite body;

};


#endif //MAIN_CPP_BULLET_H
