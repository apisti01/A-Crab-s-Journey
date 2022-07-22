//
// Created by apisti01 on 20/07/22.
//

#ifndef MAIN_CPP_STATEMAINMENU_H
#define MAIN_CPP_STATEMAINMENU_H

#include "State.h"

class StateMainMenu : public State {
public:
    explicit StateMainMenu(Game* game);
    ~StateMainMenu() override = default;

    void eventHandling(sf::Event event) override;

    void update() override { }

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background {backgroundTexture, sf::IntRect {0,0,1920,1080}} ;

};


#endif //MAIN_CPP_STATEMAINMENU_H
