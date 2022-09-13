//
// Created by longo on 02/09/2022.
//

#ifndef ACRABSJOURNEY_TEXTBUTTON_H
#define ACRABSJOURNEY_TEXTBUTTON_H

#include "Button.h"

class TextButton : public Button {
public:
    TextButton(std::string string, int characterSize, sf::Vector2f position, bool clickable = false, std::string origin = "center");

    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

    sf::Text text;

    float characterSize, minCharacterSize, maxCharacterSize;

    std::string origin;
    bool clickable, hovered;

    float timer = 0;
};


#endif //ACRABSJOURNEY_TEXTBUTTON_H
