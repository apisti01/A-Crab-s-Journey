//
// Created by longo on 24/07/2022.
//

#ifndef ACRABSJOURNEY_STATEDISPLAYMAP_H
#define ACRABSJOURNEY_STATEDISPLAYMAP_H

#include "State.h"
#include "../FloorMap.h"
#include "../Button.h"

class StateDisplayMap : public State {
public:
    explicit StateDisplayMap(Game* game);
    ~StateDisplayMap() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked) override {}

    void draw(sf::RenderWindow &window) override;

private:
    float unit;

    sf::Sprite background = { backgroundTexture, sf::IntRect(0, 0, 1920, 1080)};
    std::vector<sf::Sprite> rooms;

    sf::Texture backgroundTexture, roomTexture;

    Button mapBtn = { "Game States/DisplayMap/Map Texture.png", 1, {1920 / 2, 200}, false };
    sf::Text levelTxt;
};


#endif //ACRABSJOURNEY_STATEDISPLAYMAP_H
