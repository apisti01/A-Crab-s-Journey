//
// Created by longo on 19/08/2022.
//

#ifndef ACRABSJOURNEY_STATEBESTIARY_H
#define ACRABSJOURNEY_STATEBESTIARY_H

#include "State.h"

class StateBestiary : public State {
public:
    explicit StateBestiary(Game* game);
    ~StateBestiary() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override {}

    void draw(sf::RenderWindow &window) override;

private:
    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect {0, 0, 1920, 1080} };
};


#endif //ACRABSJOURNEY_STATEBESTIARY_H
