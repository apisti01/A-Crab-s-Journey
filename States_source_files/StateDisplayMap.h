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

    sf::Sprite background = {backgroundTexture, sf::IntRect(0, 0, 1920, 1080)};
    std::vector<sf::Sprite> rooms;

    sf::Texture backgroundTexture, roomTexture;

    TextButton mapText = {"Map", game->font, 210, {1920 / 2, 150}};
    TextButton levelText = {"Floor: " + to_string(game->map->getLevel()), game->font, 120, {150, 1080 - 150}, false, "bottomLeft"};

    SpriteButton backBtn = {"Assets/GameStates/Back Icon.png", 0.2, {150, 150}, true};
};

#endif //ACRABSJOURNEY_STATEDISPLAYMAP_H
