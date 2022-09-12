//
// Created by longo on 29/08/2022.
//

#ifndef ACRABSJOURNEY_STATEPREPARERUN_H
#define ACRABSJOURNEY_STATEPREPARERUN_H

#include "State.h"
#include "../Game.h"

class StatePrepareRun : public State {
public:
    explicit StatePrepareRun(Game *game);

    ~StatePrepareRun() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    // background
    SpriteButton background = {"Assets/GameStates/MainMenu/Background.png", 1, {.50f, .50f}};

    TextButton startRunTextBtn = {"Start Game", 150, {.50f, .14f}, true};

    // textures and buttons for the characters
    std::vector<sf::Texture> charactersTextures;
    int currCharacterIndex = 0;
    SpriteButton currCharacter = {"Assets/GameStates/PrepareRun/BrownCrab.png", 0.4, {.50f, .69f}};
    SpriteButton nextCharacterBtn = {"Assets/GameStates/PrepareRun/Next.png", 0.05, {.75f, .69f}, true};
    SpriteButton prevCharacterBtn = {"Assets/GameStates/PrepareRun/Prev.png", 0.05, {.25f, .69f}, true};

    // and for the maps
    std::vector<sf::Texture> mapsTextures;
    int currMapIndex = 0;
    SpriteButton currMap = {"Assets/GameStates/PrepareRun/CoralReef.png", 1, {.50f, .50f}};
    SpriteButton nextMapBtn = {"Assets/GameStates/PrepareRun/Next.png", 0.05, {.94f, .50f}, true};
    SpriteButton prevMapBtn = {"Assets/GameStates/PrepareRun/Prev.png", 0.05, {.06f, .50f}, true};

    SpriteButton backBtn = {"Assets/GameStates/Back Icon.png", 0.2, {.08f, .14f}, true};

    // create the player and prepare it for the run
    void setupPlayer(int characterIndex);
};


#endif //ACRABSJOURNEY_STATEPREPARERUN_H
