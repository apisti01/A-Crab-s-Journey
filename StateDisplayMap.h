//
// Created by longo on 24/07/2022.
//

#ifndef ACRABSJOURNEY_STATEDISPLAYMAP_H
#define ACRABSJOURNEY_STATEDISPLAYMAP_H

#include "State.h"
#include "FloorMap.h"

class StateDisplayMap : public State {
public:
    explicit StateDisplayMap(Game* game);
    ~StateDisplayMap() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;

private:
    std::vector<sf::RectangleShape> roomShapes;
    std::vector<sf::Text> roomTextNumbers;
    sf::RectangleShape startPointer, endPointer, shopPointer, currentPointer;

    float unit;
};


#endif //ACRABSJOURNEY_STATEDISPLAYMAP_H
