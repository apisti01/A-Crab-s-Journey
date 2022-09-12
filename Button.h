//
// Created by longo on 28/08/2022.
//

#ifndef ACRABSJOURNEY_BUTTON_H
#define ACRABSJOURNEY_BUTTON_H

#include <SFML/Graphics.hpp>

class Game;

class Button {
public:
    Button() = default;
    ~Button() = default;

    virtual void update(sf::RenderWindow &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};


#endif //ACRABSJOURNEY_BUTTON_H
