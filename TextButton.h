//
// Created by longo on 02/09/2022.
//

#ifndef ACRABSJOURNEY_TEXTBUTTON_H
#define ACRABSJOURNEY_TEXTBUTTON_H

#include "Button.h"

class TextButton : public Button {
public:
    TextButton(std::string string, sf::Font &font, int characterSize, sf::Vector2f position, bool clickable = false, std::string origin = "center");

    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

    sf::Text text;

    std::string origin;
    bool clickable;
};


#endif //ACRABSJOURNEY_TEXTBUTTON_H
