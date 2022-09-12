//
// Created by longo on 24/07/2022.
//

#ifndef ACRABSJOURNEY_STATEDISPLAYMAP_H
#define ACRABSJOURNEY_STATEDISPLAYMAP_H

#include "State.h"
#include "../Game.h"

class StateDisplayMap : public State {
public:
    explicit StateDisplayMap(Game *game);

    ~StateDisplayMap() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    float unit;

    SpriteButton background = {"Assets/GameStates/DisplayMap/" + game->map->mapType + "/Background Texture.png", 1, {.50f, .50f}};

    std::vector<sf::Sprite> rooms;

    sf::Texture backgroundTexture, roomTexture;

    TextButton mapText = {"Map", 210, {.50f, .14f}};
    TextButton levelText = {"Floor: " + to_string(game->map->getLevel()), 120, {.08f, .86f}, false, "bottomLeft"};

    SpriteButton backBtn = {"Assets/GameStates/Back Icon.png", 0.2, {.08f, .14f}, true};
};

#endif //ACRABSJOURNEY_STATEDISPLAYMAP_H
