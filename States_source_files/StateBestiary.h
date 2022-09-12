//
// Created by longo on 19/08/2022.
//

#ifndef ACRABSJOURNEY_STATEBESTIARY_H
#define ACRABSJOURNEY_STATEBESTIARY_H

#include "State.h"
#include "../Game.h"

class StateBestiary : public State {
public:
    explicit StateBestiary(Game *game);

    ~StateBestiary() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    int cols = 3;
    int rows = 3;
    int currPage = 0;

    void loadStats();

    SpriteButton background = {"Assets/GameStates/Bestiary/Background.png", 1, {.50f, .50f}};

    TextButton titleText = {"Bestiary", 210, {.50f, .14f}};

    // enemies
    int currEnemy = 0;
    std::vector<sf::Texture> enemiesTextures;
    sf::Texture enemyUnknownTexture;
    std::vector<SpriteButton> enemiesBtns;
    std::vector<SpriteButton> enemiesUnknowns;

    SpriteButton currEnemyBtn = {"Assets/GameCharacter/Enemy/AggressiveMelee/SeaTurtle/Texture.png", 0.21, {.58f, .58f}};

    // upgrade bars and stats icons
    sf::Texture upgradeUnitTexture, upgradeHalfUnitTexture;
    std::vector<SpriteButton> units;
    SpriteButton healthIcon = {"Assets/GameCharacter/Player/Stats Icons/Health.png", 0.05, {.73f, .41f}};
    SpriteButton speedIcon = {"Assets/GameCharacter/Player/Stats Icons/Speed.png", 0.05, {.73f, .52f}};
    SpriteButton armorIcon = {"Assets/GameCharacter/Player/Stats Icons/Armor.png", 0.05, {.73f, .64f}};
    SpriteButton strengthIcon = {"Assets/GameCharacter/Player/Stats Icons/Strength.png", 0.05, {.73f, .75f}};

    SpriteButton backBtn = {"Assets/GameStates/Back Icon.png", 0.2, {.08f, .14f}, true};
};


#endif //ACRABSJOURNEY_STATEBESTIARY_H
