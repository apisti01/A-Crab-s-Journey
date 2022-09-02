//
// Created by longo on 28/08/2022.
//

#ifndef ACRABSJOURNEY_BUTTON_H
#define ACRABSJOURNEY_BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(std::string texturePath, float scl, sf::Vector2f position, bool clickable = true);
    Button(std::string string, sf::Font &font, int characterSize, sf::Vector2f position, bool clickable = true, std::string origin = "center");
    ~Button() = default;

    void updateBtn(sf::RenderWindow &window);

    void drawBtn(sf::RenderWindow &window) const;
    void drawTextBtn(sf::RenderWindow &window) const;

    sf::RectangleShape box;
    sf::Texture texture;
    sf::Text btnText;

    std::string origin;
    bool clickable;
};


#endif //ACRABSJOURNEY_BUTTON_H
