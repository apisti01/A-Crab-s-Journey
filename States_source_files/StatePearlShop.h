//
// Created by longo on 26/07/2022.
//

#ifndef ACRABSJOURNEY_STATEPEARLSHOP_H
#define ACRABSJOURNEY_STATEPEARLSHOP_H

#include "State.h"
#include "../Game.h"

class StatePearlShop : public State {
public:
    explicit StatePearlShop(Game *game);

    ~StatePearlShop() override = default;

    void eventHandling(sf::Event event, sf::RenderWindow &window) override;

    void update(int deltaTime, bool clicked, sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

private:
    void reloadCharactersTextures();
    void loadStats();

    sf::Texture texture;
    sf::Sprite backgroundSprite = {texture, sf::IntRect(0, 0, 1920, 1080)};

    TextButton titleText = {"Pearl Shop", game->font, 210, {1920 / 2, 150}, false};

    // characters
    int currCharacter = 0;
    std::vector<sf::Texture> crabsTextures;
    SpriteButton currCharacterBtn = {"Game States/Pearl Shop/Brown Crab.png", 0.21, {630, 510}};
    SpriteButton currCharacterLocked = {"Game States/Pearl Shop/Locked Character.png", 0.21, {630, 510}};
    SpriteButton currCharacterCoin = {"Game States/Pearl.png", 0.15, {630, 510}};
    TextButton currCharacterPrice = {to_string(game->globalProgress.characters[currCharacter].price), game->font, 150, {630, 510}};

    SpriteButton nextCharacterBtn = {"Game States/Pearl Shop/Fiddler Crab.png", 0.15, {1050, 510}};
    SpriteButton nextCharacterLocked = {"Game States/Pearl Shop/Locked Character.png", 0.15, {1050, 510}};

    SpriteButton prevCharacterBtn = {"Game States/Pearl Shop/Asian Great Paddle.png", 0.15, {210, 510}};
    SpriteButton prevCharacterLocked = {"Game States/Pearl Shop/Locked Character.png", 0.15, {210, 510}};

    // upgrade bars and stats icons
    sf::Texture upgradeUnit;
    std::vector<sf::Sprite> upgradesBars;
    SpriteButton healthIcon = {"GameCharacter/Player/Stats Icons/Health.png", 0.05, {90, 840}};
    SpriteButton speedIcon = {"GameCharacter/Player/Stats Icons/Speed.png", 0.05, {690, 840}};
    SpriteButton armorIcon = {"GameCharacter/Player/Stats Icons/Armor.png", 0.05, {90, 960}};
    SpriteButton strengthIcon = {"GameCharacter/Player/Stats Icons/Strength.png", 0.05, {690, 960}};

    // habitats
    SpriteButton currHabitatBtn = {"Game States/Pearl Shop/Brown Crab.png", 0, {1000, 450}};
    SpriteButton nextHabitatBtn = {"Game States/Pearl Shop/Brown Crab.png", 0, {1000, 200}};
    SpriteButton prevHabitatBtn = {"Game States/Pearl Shop/Brown Crab.png", 0, {1000, 600}};

    SpriteButton backBtn = {"Game States/Back Icon.png", 0.2, {150, 150}, true};
};


#endif //ACRABSJOURNEY_STATEPEARLSHOP_H