//
// Created by longo on 24/07/2022.
//

#ifndef ACRABSJOURNEY_STATEPAUSE_H
#define ACRABSJOURNEY_STATEPAUSE_H

#include "State.h"

class StatePause : public State {
public:
    explicit StatePause(Game* game);
    ~StatePause() override = default;

    void eventHandling(sf::Event event) override;

    void update(int deltaTime) override {}

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect {0, 0, 1920, 1080} };
};


#endif //ACRABSJOURNEY_STATEPAUSE_H
