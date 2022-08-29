//
// Created by longo on 28/08/2022.
//

#ifndef ACRABSJOURNEY_BUTTON_H
#define ACRABSJOURNEY_BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(std::string texturePath, float scl, float posX, float posY, bool clickable = true);
    ~Button() = default;

    void updateBtn(sf::RenderWindow &window);

    void drawBtn(sf::RenderWindow &window);

    sf::RectangleShape btnBox;

    sf::Texture btnTexture;
};


#endif //ACRABSJOURNEY_BUTTON_H
