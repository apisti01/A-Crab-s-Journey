//
// Created by longo on 26/07/2022.
//

#ifndef ACRABSJOURNEY_STATEPEARLSHOP_H
#define ACRABSJOURNEY_STATEPEARLSHOP_H


#include "State.h"

class StatePearlShop : public State {
public:
    explicit StatePearlShop(Game* game);
    ~StatePearlShop() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;

private:
    sf::Sprite backgroundSprite;
    sf::Texture texture;
};



#endif //ACRABSJOURNEY_STATEPEARLSHOP_H
