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

    SpriteButton background = {"Assets/GameStates/PearlShop/Background.png", 1, {.50f, .50f}};

    TextButton titleText = {"Pearl Shop", 180, {.50f, .14f}};

    TextButton pearlsText = {to_string(game->globalProgress.pearls), 80, {.50f, .28f}};
    SpriteButton pearlsIcon = {"Assets/GameStates/Pearl.png", 0.035, {.50f, .28f}};

    // characters
    int currCharacter = 0;
    std::vector<sf::Texture> crabsTextures;
    SpriteButton currCharacterBtn = {"Assets/GameStates/PearlShop/BrownCrab.png", 0.21, {.33f, .53f}};
    SpriteButton currCharacterLocked = {"Assets/GameStates/PearlShop/Locked Character.png", 0.21, {.33f, .53f}};
    SpriteButton currCharacterPearl = {"Assets/GameStates/Pearl.png", 0.15, {.33f, .53f}};
    TextButton currCharacterPrice = {to_string(game->globalProgress.characters[currCharacter].price), 120, {.33f, .53f}};

    SpriteButton nextCharacterBtn = {"Assets/GameStates/PearlShop/FiddlerCrab.png", 0.15, {.55f, .53f}};
    SpriteButton nextCharacterLocked = {"Assets/GameStates/PearlShop/Locked Character.png", 0.15, {.55f, .53f}};

    SpriteButton prevCharacterBtn = {"Assets/GameStates/PearlShop/AsianGreatPaddle.png", 0.15, {.11f, .53f}};
    SpriteButton prevCharacterLocked = {"Assets/GameStates/PearlShop/Locked Character.png", 0.15, {.11f, .53f}};

    // upgrade bars and stats icons
    sf::Texture statsUnitTexture, statsHalfUnitTexture;
    std::vector<SpriteButton> units;

    SpriteButton healthBar = {"Assets/GameStates/PearlShop/Upgrade Bar.png", 1, {.18f, .81f}};
    SpriteButton healthIcon = {"Assets/GameCharacter/Player/Stats Icons/Health.png", 0.05, {.05f, .81f}};
    SpriteButton healthUp = {"Assets/GameStates/PearlShop/Upgrade Up.png", 0.035, {.29f, .81f}};
    SpriteButton healthPearl = {"Assets/GameStates/Pearl.png", 0.05, {.05f, .81f}};
    TextButton healthPrice = {to_string(25), 50, {.05f, .81f}};

    SpriteButton speedBar = {"Assets/GameStates/PearlShop/Upgrade Bar.png", 1, {.49f, .81f}};
    SpriteButton speedIcon = {"Assets/GameCharacter/Player/Stats Icons/Speed.png", 0.05, {.36f, .81f}};
    SpriteButton speedUp = {"Assets/GameStates/PearlShop/Upgrade Up.png", 0.035, {.60f, .81f}};
    SpriteButton speedPearl = {"Assets/GameStates/Pearl.png", 0.05, {.36f, .81f}};
    TextButton speedPrice = {to_string(25), 50, {.36f, .81f}};

    SpriteButton armorBar = {"Assets/GameStates/PearlShop/Upgrade Bar.png", 1, {.18f, .92f}};
    SpriteButton armorIcon = {"Assets/GameCharacter/Player/Stats Icons/Armor.png", 0.05, {.05f, .92f}};
    SpriteButton armorUp = {"Assets/GameStates/PearlShop/Upgrade Up.png", 0.035, {.29f, .92f}};
    SpriteButton armorPearl = {"Assets/GameStates/Pearl.png", 0.05, {.05f, .92f}};
    TextButton armorPrice = {to_string(25), 50, {.05f, .92f}};

    SpriteButton strengthBar = {"Assets/GameStates/PearlShop/Upgrade Bar.png", 1, {.49f, .92f}};
    SpriteButton strengthIcon = {"Assets/GameCharacter/Player/Stats Icons/Strength.png", 0.05, {.36f, .92f}};
    SpriteButton strengthUp = {"Assets/GameStates/PearlShop/Upgrade Up.png", 0.035, {.60f, .92f}};
    SpriteButton strengthPearl = {"Assets/GameStates/Pearl.png", 0.05, {.36f, .92f}};
    TextButton strengthPrice = {to_string(25), 50, {.36f, .92f}};

    // habitats
    SpriteButton currHabitatBtn = {"Assets/GameStates/PearlShop/BrownCrab.png", 0, {.52f, .41f}};
    SpriteButton nextHabitatBtn = {"Assets/GameStates/PearlShop/BrownCrab.png", 0, {.52f, .19f}};
    SpriteButton prevHabitatBtn = {"Assets/GameStates/PearlShop/BrownCrab.png", 0, {.52f, .56f}};

    SpriteButton backBtn = {"Assets/GameStates/Back Icon.png", 0.2, {.08f, .14f}, true};
};


#endif //ACRABSJOURNEY_STATEPEARLSHOP_H