//
// Created by longo on 19/08/2022.
//

#include "StateBestiary.h"

#include <iostream>

StateBestiary::StateBestiary(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Bestiary/Bestiary.png");

    auto enemies = Game::getInstance()->bestiary.beasts;
    for (int i = 0; i < size(enemies); i++) {
        // load the enemies textures
        enemiesTextures.emplace_back();
        enemiesTextures[i].loadFromFile(
                "GameCharacter/Enemy/" + enemies[i].type + "/" + enemies[i].name + "/Texture.png");
    }

    // load the enemy unknown texture
    int posX, posY;
    enemyUnknownTexture.loadFromFile("GameCharacter/Enemy/Unknown Enemy.png");
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Button enemy = {"GameCharacter/Enemy/AggressiveMelee/SeaTurtle/Texture.png", 0.09,
                            {210.0f + x * 240, 390.0f + y * 240}, false};
            enemiesBtns.push_back(enemy);

            Button enemyUnknown = {"GameCharacter/Enemy/Unknown Enemy.png", 0.09,
                                   {210.0f + x * 240, 390.0f + y * 240}, false};
            enemiesUnknowns.push_back(enemyUnknown);
        }
    }

    // load the upgrade unit texture
    upgradeUnit.loadFromFile("Game States/Pearl Shop/Upgrade Unit.png");

    loadStats();
}

void StateBestiary::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    titleText.updateBtn(window);
    backBtn.updateBtn(window);

    // update the textures
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if ((currPage * rows * cols) + (y * cols) + x < size(enemiesTextures)) {
                enemiesBtns[y * cols + x].box.setTexture(&enemiesTextures[(currPage * rows * cols) + (y * cols) + x]);
                enemiesUnknowns[y * cols + x].box.setTexture(&enemyUnknownTexture);
            }
        }
    }
}

void StateBestiary::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::B:
            case sf::Keyboard::Escape:
                game->changeState(StateType::Play);
                break;
            case sf::Keyboard::M: {
                game->changeState(StateType::DisplayMap);
                break;
            case sf::Keyboard::I:
                game->changeState(StateType::ManageInventory);
                break;
            case sf::Keyboard::P:
                game->changeState(StateType::Pause);
                break;
            }
        }
    }

    else if (event.type == sf::Event::MouseButtonPressed) {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (enemiesBtns[y * cols + x].box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                    (currPage * rows * cols) + (y * cols) + x < size(enemiesTextures)) {
                    currEnemy = (currPage * rows * cols) + (y * cols) + x;
                    loadStats();
                }
            }
        }

        if (backBtn.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);
    }
}

void StateBestiary::loadStats() {
    // load the current enemy1 texture on the right box
    currEnemyBtn.box.setTexture(&enemiesTextures[currEnemy]);

    // and all his stats
    auto enemy = Game::getInstance()->bestiary.beasts[currEnemy];
    upgradesBars = {};
    sf::Sprite upgradeBar;
    // health upgrades
    for (int i = 1; i <= enemy.health; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(1410 + 40 * i, 450);
        upgradeBar.setScale(0.02, 0.03);
        upgradesBars.push_back(upgradeBar);
    }

    // speed upgrades
    for (int i = 1; i <= enemy.speed; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(1410 + 40 * i, 570);
        upgradeBar.setScale(0.02, 0.03);
        upgradesBars.push_back(upgradeBar);
    }

    // armor upgrades
    for (int i = 1; i <= enemy.armor; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(1410 + 40 * i, 690);
        upgradeBar.setScale(0.02, 0.03);
        upgradesBars.push_back(upgradeBar);
    }

    // strength upgrades
    for (int i = 1; i <= enemy.strength; i++) {
        upgradeBar.setTexture(upgradeUnit);
        upgradeBar.setOrigin(upgradeUnit.getSize().x / 2, upgradeUnit.getSize().y / 2);
        upgradeBar.setPosition(1410 + 40 * i, 810);
        upgradeBar.setScale(0.02, 0.03);
        upgradesBars.push_back(upgradeBar);
    }
}

void StateBestiary::draw(sf::RenderWindow &window) {
    // draw the background and the title text
    window.draw(background);
    titleText.drawTextBtn(window);
    backBtn.drawBtn(window);

    // draw the enemies
    auto enemies = Game::getInstance()->bestiary.beasts;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            enemiesBtns[y * cols + x].drawBtn(window);
            if ((currPage * rows * cols) + (y * cols) + x < size(enemies) &&
                !enemies[(currPage * rows * cols) + (y * cols) + x].discovered)
                enemiesUnknowns[y * cols + x].drawBtn(window);
        }
    }
    // and the selected one
    currEnemyBtn.drawBtn(window);

    // draw the stats upgrades
    for (int i = 0; i < size(upgradesBars); i++)
        window.draw(upgradesBars[i]);

    // draw the stats icons
    healthIcon.drawBtn(window);
    speedIcon.drawBtn(window);
    armorIcon.drawBtn(window);
    strengthIcon.drawBtn(window);
}
