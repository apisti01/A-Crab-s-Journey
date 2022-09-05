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

    // load the upgrade lenUnit texture
    statsUnitTexture.loadFromFile("Game States/Pearl Shop/Stats Unit.png");
    statsHalfUnitTexture.loadFromFile("Game States/Pearl Shop/Stats Half Unit.png");

    loadStats();
}

void StatePearlShop::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    titleText.update(window);

    // pearls info position
    pearlsText.text.setString(to_string(game->globalProgress.pearls));
    pearlsText.update(window);
    int pearlsInfoWidth = pearlsText.text.getGlobalBounds().width + pearlsIcon.rect.getGlobalBounds().width - 50;
    pearlsText.text.setPosition(1920 / 2 - pearlsInfoWidth / 2, pearlsText.text.getPosition().y);
    pearlsIcon.rect.setPosition(1920 / 2 + pearlsInfoWidth / 2, pearlsIcon.rect.getPosition().y);

    // go back button
    backBtn.update(window);

    // upgrades prices
    healthPrice.text.setString(to_string(int(25 * (game->globalProgress.characters[currCharacter].healthUpgrades + 1))));
    healthPrice.update(window);
    speedPrice.text.setString(to_string(int(25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1))));
    speedPrice.update(window);
    armorPrice.text.setString(to_string(int(25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1))));
    armorPrice.update(window);
    strengthPrice.text.setString(to_string(int(25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1))));
    strengthPrice.update(window);

    // characters price
    currCharacterPrice.update(window);
    currCharacterPrice.text.setString(to_string(game->globalProgress.characters[currCharacter].price));
}

void StatePearlShop::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                game->changeState(StateType::MainMenu);
                break;
            case sf::Keyboard::Right:
            case sf::Keyboard::D:
                currCharacter = (currCharacter + 1) % size(crabsTextures);
                reloadCharactersTextures();
                loadStats();
                break;
            case sf::Keyboard::Left:
            case sf::Keyboard::A:
                currCharacter = (currCharacter - 1 + size(crabsTextures)) % size(crabsTextures);
                reloadCharactersTextures();
                loadStats();
                break;
        }
    }

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
            loadStats();
            game->globalProgress.updateTxtFile();
        }
        else if (speedUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                 game->globalProgress.characters[currCharacter].unlocked && game->globalProgress.characters[currCharacter].speedUpgrades < 4 &&
                 game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1)) {
            game->globalProgress.pearls -= 25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1);
            game->globalProgress.characters[currCharacter].speedUpgrades++;
            loadStats();
            game->globalProgress.updateTxtFile();
        }
        else if (armorUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                 game->globalProgress.characters[currCharacter].unlocked && game->globalProgress.characters[currCharacter].armorUpgrades < 4 &&
                 game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1)) {
            game->globalProgress.pearls -= 25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1);
            game->globalProgress.characters[currCharacter].armorUpgrades++;
            loadStats();
            game->globalProgress.updateTxtFile();
        }
        else if (strengthUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                 game->globalProgress.characters[currCharacter].unlocked && game->globalProgress.characters[currCharacter].strengthUpgrades < 4 &&
                 game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1)) {
            game->globalProgress.pearls -= 25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1);
            game->globalProgress.characters[currCharacter].strengthUpgrades++;
            loadStats();
            game->globalProgress.updateTxtFile();
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
    auto character = Game::getInstance()->globalProgress.characters[currCharacter];

    units = {};

    int i;
    // health upgrades
    for (i = 0; i < floor(character.health + character.healthUpgrades / 2); i++)
        units.push_back({statsUnitTexture, 0.025, {140.0f + 55 * i, 870}});
    if (fmod(character.health + character.healthUpgrades / 2, 1) != 0)
        units.push_back({statsHalfUnitTexture, 0.025, {140.0f + 55 * i - 12.5f, 870}});

    // speed upgrades
    for (i = 0; i < floor(character.speed + character.speedUpgrades / 2); i++)
        units.push_back({statsUnitTexture, 0.025, {740.0f + 55 * i, 870}});
    if (fmod(character.speed + character.speedUpgrades / 2, 1) != 0)
        units.push_back({statsHalfUnitTexture, 0.025, {740.0f + 55 * i - 12.5f, 870}});

    // armor upgrades
    for (i = 0; i < floor(character.armor + character.armorUpgrades / 2); i++)
        units.push_back({statsUnitTexture, 0.025, {140.0f + 55 * i, 990}});
    if (fmod(character.armor + character.armorUpgrades / 2, 1) != 0)
        units.push_back({statsHalfUnitTexture, 0.025, {140.0f + 55 * i - 12.5f, 990}});

    // strength upgrades
    for (i = 0; i < floor(character.strength + character.strengthUpgrades / 2); i++)
        units.push_back({statsUnitTexture, 0.025, {740.0f + 55 * i, 990}});
    if (fmod(character.strength + character.strengthUpgrades / 2, 1) != 0)
        units.push_back({statsHalfUnitTexture, 0.025, {740.0f + 55 * i - 12.5f, 990}});
}

void StatePearlShop::draw(sf::RenderWindow &window) {
    // draw the background and the title
    window.draw(backgroundSprite);
    titleText.draw(window);

    // draw the pearl icon and write the number of pearls owned
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

    // if mouse is on the current character and it's a locked character
    if (currCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        !game->globalProgress.characters[currCharacter].unlocked) {
        currCharacterPearl.draw(window);

        // if you can afford the price the text color is white, otherwise is red
        if (game->globalProgress.pearls >= game->globalProgress.characters[currCharacter].price)
            currCharacterPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            currCharacterPrice.text.setFillColor(sf::Color(243, 29, 44));

        currCharacterPrice.draw(window);
    }

    // draw the stats bars
    healthBar.draw(window);
    speedBar.draw(window);
    armorBar.draw(window);
    strengthBar.draw(window);

    for (int i = 0; i < size(units); i++)
        units[i].draw(window);
    
    healthIcon.draw(window);
    speedIcon.draw(window);
    armorIcon.draw(window);
    strengthIcon.draw(window);

    if (game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].healthUpgrades < 4)
        healthUp.draw(window);
    if (game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].speedUpgrades < 4)
        speedUp.draw(window);
    if (game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].armorUpgrades < 4)
        armorUp.draw(window);
    if (game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].strengthUpgrades < 4)
        strengthUp.draw(window);

    if (healthUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].healthUpgrades < 4) {
        healthPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].healthUpgrades + 1))
            healthPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            healthPrice.text.setFillColor(sf::Color(243, 29, 44));
        healthPrice.draw(window);
    }

    if (speedUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].speedUpgrades < 4) {
        speedPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].speedUpgrades + 1))
            speedPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            speedPrice.text.setFillColor(sf::Color(243, 29, 44));
        speedPrice.draw(window);
    }

    if (armorUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].armorUpgrades < 4) {
        armorPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].armorUpgrades + 1))
            armorPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            armorPrice.text.setFillColor(sf::Color(243, 29, 44));
        armorPrice.draw(window);
    }

    if (strengthUp.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
        game->globalProgress.characters[currCharacter].unlocked &&
        game->globalProgress.characters[currCharacter].strengthUpgrades < 4) {
        strengthPearl.draw(window);
        if (game->globalProgress.pearls >= 25 * (game->globalProgress.characters[currCharacter].strengthUpgrades + 1))
            strengthPrice.text.setFillColor(sf::Color(255, 255, 255));
        else
            strengthPrice.text.setFillColor(sf::Color(243, 29, 44));
        strengthPrice.draw(window);
    }

    // draw the habitats
    currHabitatBtn.draw(window);
    nextHabitatBtn.draw(window);
    prevHabitatBtn.draw(window);

    backBtn.draw(window);
}