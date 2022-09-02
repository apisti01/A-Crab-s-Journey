//
// Created by longo on 19/08/2022.
//

#ifndef ACRABSJOURNEY_STATEBESTIARY_H
#define ACRABSJOURNEY_STATEBESTIARY_H

#include "State.h"
#include "../Game.h"
#include "../Button.h"

class StateBestiary : public State {
public:
    explicit StateBestiary(Game* game);
    ~StateBestiary() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    int cols = 3;
    int rows = 3;
    int currPage = 0;

    void loadStats();

    sf::Texture backgroundTexture;
    sf::Sprite background { backgroundTexture, sf::IntRect {0, 0, 1920, 1080} };

    Button titleText = {"Bestiary", game->font, 210, {1920 / 2, 150}, false};

    // enemies
    int currEnemy = 0;
    std::vector<sf::Texture> enemiesTextures;
    sf::Texture enemyUnknownTexture;
    std::vector<Button> enemiesBtns;
    std::vector<Button> enemiesUnknowns;

    Button currEnemyBtn = {"GameCharacter/Enemy/AggressiveMelee/SeaTurtle/Texture.png", 0.21, {1110, 630}, false};

    // upgrade bars and stats icons
    sf::Texture upgradeUnit;
    std::vector<sf::Sprite> upgradesBars;
    Button healthIcon = {"GameCharacter/Player/Stats Icons/Health.png", 0.05, {1410, 450}, false};
    Button speedIcon = {"GameCharacter/Player/Stats Icons/Speed.png", 0.05, {1410, 570}, false};
    Button armorIcon = {"GameCharacter/Player/Stats Icons/Armor.png", 0.05, {1410, 690}, false};
    Button strengthIcon = {"GameCharacter/Player/Stats Icons/Strength.png", 0.05, {1410, 810}, false};

    Button backBtn = {"Game States/Back Icon.png", 0.2, {150, 150}};
};


#endif //ACRABSJOURNEY_STATEBESTIARY_H
