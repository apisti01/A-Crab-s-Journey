//
// Created by longo on 26/07/2022.
//

#ifndef ACRABSJOURNEY_STATESETTINGS_H
#define ACRABSJOURNEY_STATESETTINGS_H

#include "State.h"
#include "../Button.h"

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

    Button settingsText = {"Settings", game->font, 240, {1920 / 2, 175}, false};
    Button languageText = {"Language", game->font, 150, {1920 / 4, 450}, false};
    Button difficultyText = {"Difficulty", game->font, 150, {1920 / 4, 600}, false};
    Button soundText = {"Sound", game->font, 150, {1920 / 4, 750}, false};
};

#endif //ACRABSJOURNEY_STATESETTINGS_H
