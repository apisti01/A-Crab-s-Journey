//
// Created by longo on 26/07/2022.
//

#include "StatePearlShop.h"

StatePearlShop::StatePearlShop(Game *game) : State(game) {
    texture.loadFromFile("Games States/Pearl Shop/Pearl Shop.png");

    // load the characters textures
    crabsTextures.emplace_back();
    crabsTextures[0].loadFromFile("Games States/Pearl Shop/Brown Crab.png");
    crabsTextures.emplace_back();
    crabsTextures[1].loadFromFile("Games States/Pearl Shop/Fiddler Crab.png");
    crabsTextures.emplace_back();
    crabsTextures[2].loadFromFile("Games States/Pearl Shop/Triangle Tanner Crab.png");
    crabsTextures.emplace_back();
    crabsTextures[3].loadFromFile("Games States/Pearl Shop/Asian Great Paddle.png");

    // load the locked texture
    lockedCharacterTexture.loadFromFile("Games States/Pearl Shop/Locked Character.png");
    currCharacterLocked.setScale(0.225, 0.225);
    currCharacterLocked.setOrigin(lockedCharacterTexture.getSize().x / 2, lockedCharacterTexture.getSize().y / 2);

    // load the upgrade unit texture
    upgradeUnit.loadFromFile("Games States/Pearl Shop/Upgrade Unit.png");

    loadStats();
}

void StatePearlShop::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::MainMenu);

    else if (event.type == sf::Event::MouseButtonReleased) {
        // scroll characters from right to left
        if (nextCharacterBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            currCharacter = (currCharacter + 1) % size(crabsTextures);
            reloadCharactersTextures();
            loadStats();
        }
        // scroll characters from left to right
        else if (prevCharacterBtn.btnBox.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            currCharacter = (currCharacter - 1 + size(crabsTextures)) % size(crabsTextures);
            reloadCharactersTextures();
            loadStats();
        }
    }
}

void StatePearlShop::reloadCharactersTextures() {
    currCharacterBtn.btnBox.setTexture(&crabsTextures[currCharacter]);
    nextCharacterBtn.btnBox.setTexture(&crabsTextures[(currCharacter + 1) % size(crabsTextures)]);
    prevCharacterBtn.btnBox.setTexture(&crabsTextures[(currCharacter - 1 + size(crabsTextures)) % size(crabsTextures)]);
}

void StatePearlShop::loadStats() {
    auto characters = Game::getInstance()->globalProgress.characters;

    int i;
    upgradesBars = {};

    sf::Sprite upgradeBar;
    // health upgrades
    for (i = 0; i < characters[currCharacter].health; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(90 + 60 * i, 840);
        upgradeBar.setScale(0.03, 0.03);
        upgradesBars.push_back(upgradeBar);
    }

    // health upgrades
    for (i = 0; i < characters[currCharacter].speed; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(690 + 60 * i, 840);
        upgradeBar.setScale(0.03, 0.03);
        upgradesBars.push_back(upgradeBar);
    }

    // health upgrades
    for (i = 0; i < characters[currCharacter].armor; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(90 + 60 * i, 960);
        upgradeBar.setScale(0.03, 0.03);
        upgradesBars.push_back(upgradeBar);
    }

    // health upgrades
    for (i = 0; i < characters[currCharacter].strength; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(690 + 60 * i, 960);
        upgradeBar.setScale(0.03, 0.03);
        upgradesBars.push_back(upgradeBar);
    }
}

void StatePearlShop::draw(sf::RenderWindow &window) {
    window.draw(backgroundSprite);

    // draw the characters
    currCharacterBtn.drawBtn(window);
    nextCharacterBtn.drawBtn(window);
    prevCharacterBtn.drawBtn(window);

    // draw the habitats
    currHabitatBtn.drawBtn(window);
    nextHabitatBtn.drawBtn(window);
    prevHabitatBtn.drawBtn(window);

    // draw the stats upgrades
    for (int i = 0; i < size(upgradesBars); i++)
        window.draw(upgradesBars[i]);

    // draw the stats icons
    healthIcon.drawBtn(window);
    speedIcon.drawBtn(window);
    armorIcon.drawBtn(window);
    strengthIcon.drawBtn(window);
}