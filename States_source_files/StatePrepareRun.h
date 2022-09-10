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
    sf::Texture backgroundTexture;
    sf::Sprite background{backgroundTexture, sf::IntRect{0, 0, 1920, 1080}};

    TextButton startRunTextBtn = {"Start Game", game->font, 150, {1920 / 2, 150}, true};

    // textures and buttons for the characters
    std::vector<sf::Texture> charactersTextures;
    int currCharacterIndex = 0;
    SpriteButton currCharacter = {"Assets/GameStates/PrepareRun/BrownCrab.png", 0.4, {1920 / 2, 750}};
    SpriteButton nextCharacterBtn = {"Assets/GameStates/PrepareRun/Next.png", 0.05, {1920 / 2 + 500, 750}, true};
    SpriteButton prevCharacterBtn = {"Assets/GameStates/PrepareRun/Prev.png", 0.05, {1920 / 2 - 500, 750}, true};

    // and for the maps
    std::vector<sf::Texture> mapsTextures;
    int currMapIndex = 0;
    SpriteButton currMap = {"Assets/GameStates/PrepareRun/CoralReef.png", 1, {1920 / 2, 1080 / 2}};
    SpriteButton nextMapBtn = {"Assets/GameStates/PrepareRun/Next.png", 0.05, {1920 - 100, 1080 / 2}, true};
    SpriteButton prevMapBtn = {"Assets/GameStates/PrepareRun/Prev.png", 0.05, {100, 1080 / 2}, true};

    SpriteButton backBtn = {"Assets/GameStates/Back Icon.png", 0.2, {150, 150}, true};

    // create the player and prepare it for the run
    void setupPlayer(int characterIndex);
};


#endif //ACRABSJOURNEY_STATEPREPARERUN_H
