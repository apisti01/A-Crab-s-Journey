//
// Created by longo on 29/08/2022.
//

#ifndef ACRABSJOURNEY_STATEPREPARERUN_H
#define ACRABSJOURNEY_STATEPREPARERUN_H

#include "../Game.h"
#include "../Button.h"
#include "State.h"

class StatePrepareRun : public State {
public:
    explicit StatePrepareRun(Game *game);

    ~StatePrepareRun() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    // background
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect{0, 0, 1920, 1080}};

    Button startRunTextBtn = {"Start Game", game->font, 180, sf::Vector2f{1920 / 2, 1080 / 2}};

    Button backBtn = {"Game States/Back Icon.png", 0.2, {100, 100}};

    int selectedCharacter = 0;
    int selectedMap = 0;

    //  create the player and prepare it for the game
    void setupPlayer(int characterIndex);
};


#endif //ACRABSJOURNEY_STATEPREPARERUN_H
