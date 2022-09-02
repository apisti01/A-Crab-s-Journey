//
// Created by longo on 02/09/2022.
//

#ifndef ACRABSJOURNEY_SPRITEBUTTON_H
#define ACRABSJOURNEY_SPRITEBUTTON_H

#include "Button.h"

class SpriteButton : public Button {
public:
    SpriteButton(std::string texturePath, float scl, sf::Vector2f position, bool clickable = false, std::string origin = "center");

    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

    sf::RectangleShape rect;
    sf::Texture texture;

    std::string origin;
    bool clickable;
};


#endif //ACRABSJOURNEY_SPRITEBUTTON_H
