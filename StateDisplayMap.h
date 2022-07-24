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

    void eventHandling(sf::Event event) override;

    void update(int deltaTime) override {}

    void draw(sf::RenderWindow &window) override;

private:
    std::vector<sf::RectangleShape> roomShapes;
    std::vector<sf::Text> roomTextNumbers;
    sf::CircleShape startPointer, endPointer, shopPointer, currentPointer;
};


#endif //ACRABSJOURNEY_STATEDISPLAYMAP_H
