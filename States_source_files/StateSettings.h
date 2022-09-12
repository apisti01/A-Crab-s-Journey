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
    SpriteButton background = {"Assets/GameStates/PauseScreen/Background.png", 1, {.50f, .50f}};

    TextButton settingsText = {"Settings", 210, {.50f, .14f}};
    TextButton difficultyText = {"Difficulty", 150, {.25f, .42f}};
    TextButton languageText = {"Language", 150, {.25f, .55f}};
    TextButton soundText = {"Sound", 150, {.25f, .69f}};

    SpriteButton backBtn = {"Assets/GameStates/Back Icon.png", 0.2, {.08f, .14f}, true};
};

#endif //ACRABSJOURNEY_STATESETTINGS_H
