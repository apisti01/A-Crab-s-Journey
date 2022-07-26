//
// Created by longo on 26/07/2022.
//

#ifndef ACRABSJOURNEY_STATESETTINGS_H
#define ACRABSJOURNEY_STATESETTINGS_H

#include "State.h"

class StateSettings : public State {
public:
    explicit StateSettings(Game* game);
    ~StateSettings() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;
    sf::Texture texture;
};

#endif //ACRABSJOURNEY_STATESETTINGS_H