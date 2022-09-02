//
// Created by longo on 26/07/2022.
//

#ifndef ACRABSJOURNEY_STATESETTINGS_H
#define ACRABSJOURNEY_STATESETTINGS_H

#include "State.h"
#include "../Game.h"

class StateSettings : public State {
public:
    explicit StateSettings(Game *game);

    ~StateSettings() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    sf::Texture texture;
    sf::Sprite backgroundSprite = {texture, sf::IntRect(0, 0, 1920, 1080)};

    TextButton settingsText = {"Settings", game->font, 210, {1920 / 2, 150}};
    TextButton difficultyText = {"Difficulty", game->font, 150, {1920 / 4, 450}};
    TextButton languageText = {"Language", game->font, 150, {1920 / 4, 600}};
    TextButton soundText = {"Sound", game->font, 150, {1920 / 4, 750}};

    SpriteButton backBtn = {"Game States/Back Icon.png", 0.2, {150, 150}, true};
};

#endif //ACRABSJOURNEY_STATESETTINGS_H
