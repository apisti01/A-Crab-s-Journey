//
// Created by longo on 26/07/2022.
//

#include "StatePearlShop.h"

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
    upgradeUnit.loadFromFile("Game States/Pearl Shop/Upgrade Unit.png");

    loadStats();
}

void StatePearlShop::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    backBtn.updateBtn(window);

    currCharacterPrice.btnText.setString(to_string(game->globalProgress.characters[currCharacter].price));
}

void StatePearlShop::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::MainMenu);

    else if (event.type == sf::Event::MouseButtonReleased) {
        // scroll characters from right to left
        if (nextCharacterBtn.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            currCharacter = (currCharacter + 1) % size(crabsTextures);
            reloadCharactersTextures();
            loadStats();
        }
        // scroll characters from left to right
        else if (prevCharacterBtn.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            currCharacter = (currCharacter - 1 + size(crabsTextures)) % size(crabsTextures);
            reloadCharactersTextures();
            loadStats();
        }

        else if (backBtn.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);
    }
}

void StatePearlShop::reloadCharactersTextures() {
    currCharacterBtn.box.setTexture(&crabsTextures[currCharacter]);
    nextCharacterBtn.box.setTexture(&crabsTextures[(currCharacter + 1) % size(crabsTextures)]);
    prevCharacterBtn.box.setTexture(&crabsTextures[(currCharacter - 1 + size(crabsTextures)) % size(crabsTextures)]);
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
    auto characters = Game::getInstance()->globalProgress.characters;
    currCharacterBtn.drawBtn(window);
    if (!characters[currCharacter].unlocked)
        currCharacterLocked.drawBtn(window);

    nextCharacterBtn.drawBtn(window);
    if (!characters[(currCharacter + 1) % size(characters)].unlocked)
        nextCharacterLocked.drawBtn(window);

    prevCharacterBtn.drawBtn(window);
    if (!characters[(currCharacter - 1 + size(characters)) % size(characters)].unlocked)
        prevCharacterLocked.drawBtn(window);

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

    // if mouse is on the current character and it's a locked character
    if (currCharacterCoin.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        !game->globalProgress.characters[currCharacter].unlocked) {
        currCharacterCoin.drawBtn(window);
        currCharacterPrice.drawTextBtn(window);
    }

    backBtn.drawBtn(window);
}