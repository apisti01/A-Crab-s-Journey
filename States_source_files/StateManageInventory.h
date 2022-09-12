//
// Created by longo on 26/07/2022.
//

#ifndef ACRABSJOURNEY_STATEMANAGEINVENTORY_H
#define ACRABSJOURNEY_STATEMANAGEINVENTORY_H

#include "State.h"
#include "../Game.h"

class StateManageInventory : public State {
public:
    explicit StateManageInventory(Game *game);

    ~StateManageInventory() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override {}

    void draw(sf::RenderWindow &window) override;

private:
    // background
    SpriteButton background = {"Assets/GameStates/Inventory/Background.png", 1, {.50f, .50f}};
};


#endif //ACRABSJOURNEY_STATEMANAGEINVENTORY_H
