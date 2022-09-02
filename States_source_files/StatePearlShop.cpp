//
// Created by longo on 26/07/2022.
//

#include "StatePearlShop.h"

#include <iostream>

StatePearlShop::StatePearlShop(Game *game) : State(game) {
    texture.loadFromFile("Game States/Pearl Shop/Pearl Shop.png");

    // load the characters textures
    crabsTextures.emplace_back();
    crabsTextures[0].loadFromFile("Game States/Pearl Shop/Brown Crab.png");
    crabsTextures.emplace_back();
    crabsTextures[1].loadFromFile("Game States/Pearl Shop/Fiddler Crab.png");
    crabsTextures.emplace_back();
    crabsTextures[2].loadFromFile("Game States/Pearl Shop/Triangle Tanner Crab.png");
    crabsTextures.emplace_back();
    crabsTextures[3].loadFromFile("Game States/Pearl Shop/Asian Great Paddle.png");

    // load the upgrade unit texture
    upgradeUnitTexture.loadFromFile("Game States/Pearl Shop/Upgrade Unit.png");

    loadStats();
}

void StatePearlShop::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    titleText.update(window);
    pearlsText.text.setString(to_string(game->globalProgress.pearls));
    pearlsText.update(window);
    backBtn.update(window);

    healthPrice.text.setString(to_string(25 * (game->globalProgress.characters[currCharacter].healthUpgrades + 1)));
    healthPrice.update(window);
    speedPrice.text.setString(to_string(25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1)));
    speedPrice.update(window);
    armorPrice.text.setString(to_string(25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1)));
    armorPrice.update(window);
    strengthPrice.text.setString(to_string(25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1)));
    strengthPrice.update(window);

    currCharacterPrice.update(window);
    currCharacterPrice.text.setString(to_string(game->globalProgress.characters[currCharacter].price));
}

void StatePearlShop::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::MainMenu);

    else if (event.type == sf::Event::MouseButtonReleased) {
        // scroll characters from right to left
        if (nextCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            currCharacter = (currCharacter + 1) % size(crabsTextures);
            reloadCharactersTextures();
            loadStats();
        }
        // scroll characters from left to right
        else if (prevCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            currCharacter = (currCharacter - 1 + size(crabsTextures)) % size(crabsTextures);
            reloadCharactersTextures();
            loadStats();
        }
        // if current character is clicked, it is locked and you have pears needed
        else if (currCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                !game->globalProgress.characters[currCharacter].unlocked &&
                game->globalProgress.pearls >= game->globalProgress.characters[currCharacter].price) {
            // buy the character
            game->globalProgress.unlockCharacter(currCharacter);
        }

        else if (healthUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                 game->globalProgress.characters[currCharacter].unlocked && game->globalProgress.characters[currCharacter].healthUpgrades < 4 &&
                 game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].healthUpgrades + 1)) {
            game->globalProgress.pearls -= 25 * (game->globalProgress.characters[currCharacter].healthUpgrades + 1);
            game->globalProgress.characters[currCharacter].healthUpgrades++;
            game->globalProgress.updateTxtFile();
            loadStats();
        }
        else if (speedUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                 game->globalProgress.characters[currCharacter].unlocked && game->globalProgress.characters[currCharacter].speedUpgrades < 4 &&
                 game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1)) {
            game->globalProgress.pearls -= 25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1);
            game->globalProgress.characters[currCharacter].speedUpgrades++;
            game->globalProgress.updateTxtFile();
            loadStats();
        }
        else if (armorUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                 game->globalProgress.characters[currCharacter].unlocked && game->globalProgress.characters[currCharacter].armorUpgrades < 4 &&
                 game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1)) {
            game->globalProgress.pearls -= 25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1);
            game->globalProgress.characters[currCharacter].armorUpgrades++;
            game->globalProgress.updateTxtFile();
            loadStats();
        }
        else if (strengthUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                 game->globalProgress.characters[currCharacter].unlocked && game->globalProgress.characters[currCharacter].strengthUpgrades < 4 &&
                 game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1)) {
            game->globalProgress.pearls -= 25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1);
            game->globalProgress.characters[currCharacter].strengthUpgrades++;
            game->globalProgress.updateTxtFile();
            loadStats();
        }

        else if (backBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);
    }
}

void StatePearlShop::reloadCharactersTextures() {
    currCharacterBtn.rect.setTexture(&crabsTextures[currCharacter]);
    nextCharacterBtn.rect.setTexture(&crabsTextures[(currCharacter + 1) % size(crabsTextures)]);
    prevCharacterBtn.rect.setTexture(&crabsTextures[(currCharacter - 1 + size(crabsTextures)) % size(crabsTextures)]);
}

void StatePearlShop::loadStats() {
    auto characters = Game::getInstance()->globalProgress.characters;

    int i;
    upgradesUnits = {};

    sf::Sprite upgradeUnit;
    // health upgrades
    for (i = 0; i < characters[currCharacter].health + characters[currCharacter].healthUpgrades / 2; i++) {
        upgradeUnit.setTexture(upgradeUnitTexture);
        upgradeUnit.setOrigin(upgradeUnitTexture.getSize().x / 2, upgradeUnitTexture.getSize().y / 2);
        upgradeUnit.setPosition(90 + 60 * i, 840);
        upgradeUnit.setScale(0.03, 0.03);
        upgradesUnits.push_back(upgradeUnit);
    }

    // speed upgrades
    for (i = 0; i < characters[currCharacter].speed + characters[currCharacter].speedUpgrades / 2; i++) {
        upgradeUnit.setTexture(upgradeUnitTexture);
        upgradeUnit.setOrigin(upgradeUnitTexture.getSize().x / 2, upgradeUnitTexture.getSize().y / 2);
        upgradeUnit.setPosition(690 + 60 * i, 840);
        upgradeUnit.setScale(0.03, 0.03);
        upgradesUnits.push_back(upgradeUnit);
    }

    // armor upgrades
    for (i = 0; i < characters[currCharacter].armor + characters[currCharacter].armorUpgrades / 2; i++) {
        upgradeUnit.setTexture(upgradeUnitTexture);
        upgradeUnit.setOrigin(upgradeUnitTexture.getSize().x / 2, upgradeUnitTexture.getSize().y / 2);
        upgradeUnit.setPosition(90 + 60 * i, 960);
        upgradeUnit.setScale(0.03, 0.03);
        upgradesUnits.push_back(upgradeUnit);
    }

    // strength upgrades
    for (i = 0; i < characters[currCharacter].strength + characters[currCharacter].strengthUpgrades / 2; i++) {
        upgradeUnit.setTexture(upgradeUnitTexture);
        upgradeUnit.setOrigin(upgradeUnitTexture.getSize().x / 2, upgradeUnitTexture.getSize().y / 2);
        upgradeUnit.setPosition(690 + 60 * i, 960);
        upgradeUnit.setScale(0.03, 0.03);
        upgradesUnits.push_back(upgradeUnit);
    }
}

void StatePearlShop::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);

    titleText.draw(window);
    pearlsText.draw(window);
    pearlsIcon.draw(window);

    // draw the characters
    auto characters = Game::getInstance()->globalProgress.characters;
    currCharacterBtn.draw(window);
    if (!characters[currCharacter].unlocked)
        currCharacterLocked.draw(window);

    nextCharacterBtn.draw(window);
    if (!characters[(currCharacter + 1) % size(characters)].unlocked)
        nextCharacterLocked.draw(window);

    prevCharacterBtn.draw(window);
    if (!characters[(currCharacter - 1 + size(characters)) % size(characters)].unlocked)
        prevCharacterLocked.draw(window);

    // draw the habitats
    currHabitatBtn.draw(window);
    nextHabitatBtn.draw(window);
    prevHabitatBtn.draw(window);

    healthBar.draw(window);
    speedBar.draw(window);
    armorBar.draw(window);
    strengthBar.draw(window);

    // draw the stats upgrades
    for (int i = 0; i < size(upgradesUnits); i++)
        window.draw(upgradesUnits[i]);

    // draw the stats icons
    healthIcon.draw(window);
    speedIcon.draw(window);
    armorIcon.draw(window);
    strengthIcon.draw(window);

    if (game->globalProgress.characters[currCharacter].healthUpgrades < 4)
        healthUp.draw(window);
    if (game->globalProgress.characters[currCharacter].speedUpgrades < 4)
        speedUp.draw(window);
    if (game->globalProgress.characters[currCharacter].armorUpgrades < 4)
        armorUp.draw(window);
    if (game->globalProgress.characters[currCharacter].strengthUpgrades < 4)
        strengthUp.draw(window);

    if (healthUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].healthUpgrades < 4) {
        healthPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].healthUpgrades + 1))
            healthPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            healthPrice.text.setFillColor(sf::Color(243, 29, 44));
        healthPrice.draw(window);
    }

    if (speedUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].speedUpgrades < 4) {
        speedPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1))
            speedPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            speedPrice.text.setFillColor(sf::Color(243, 29, 44));
        speedPrice.draw(window);
    }

    if (armorUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].armorUpgrades < 4) {
        armorPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1))
            armorPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            armorPrice.text.setFillColor(sf::Color(243, 29, 44));
        armorPrice.draw(window);
    }

    if (strengthUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].strengthUpgrades < 4) {
        strengthPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1))
            strengthPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            strengthPrice.text.setFillColor(sf::Color(243, 29, 44));
        strengthPrice.draw(window);
    }

    // if mouse is on the current character and it's a locked character
    if (currCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        !game->globalProgress.characters[currCharacter].unlocked) {
        currCharacterCoin.draw(window);

        // if you can afford the price the text color is white, otherwise is red
        if (game->globalProgress.pearls >= game->globalProgress.characters[currCharacter].price)
            currCharacterPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            currCharacterPrice.text.setFillColor(sf::Color(243, 29, 44));

        currCharacterPrice.draw(window);
    }

    backBtn.draw(window);
}