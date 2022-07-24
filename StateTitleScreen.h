//
// Created by apisti01 on 20/07/22.
//

#ifndef MAIN_CPP_STATETITLESCREEN_H
#define MAIN_CPP_STATETITLESCREEN_H

#include "State.h"

class StateTitleScreen : public State {
public:
    // Constructor and Destructor
    explicit StateTitleScreen(Game* game);
    ~StateTitleScreen() override = default;

    void eventHandling(sf::Event event) override;

    void update(int deltaTime) override {}

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect(0, 0, 1920, 1080) };
};


#endif //MAIN_CPP_STATETITLESCREEN_H
