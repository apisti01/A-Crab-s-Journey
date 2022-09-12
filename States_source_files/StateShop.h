//
// Created by longo on 26/07/2022.
//

#ifndef ACRABSJOURNEY_STATESHOP_H
#define ACRABSJOURNEY_STATESHOP_H

#include "State.h"
#include "../Game.h"

class StateShop : public State {
public:
    explicit StateShop(Game* game);
    ~StateShop() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override {}

    void draw(sf::RenderWindow &window) override;

private:
    SpriteButton background = {"Assets/GameStates/Shop/Background.png", 1, {.50f, .50f}};
};


#endif //ACRABSJOURNEY_STATESHOP_H
