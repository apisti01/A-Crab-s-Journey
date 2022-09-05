//
// Created by longo on 19/08/2022.
//

#include "StateBestiary.h"

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
            SpriteButton enemy = {"GameCharacter/Enemy/AggressiveMelee/SeaTurtle/Texture.png", 0.09,
                            {210.0f + x * 240, 390.0f + y * 240}, false};
            enemiesBtns.push_back(enemy);

            SpriteButton enemyUnknown = {"GameCharacter/Enemy/Unknown Enemy.png", 0.09,
                                   {210.0f + x * 240, 390.0f + y * 240}, false};
            enemiesUnknowns.push_back(enemyUnknown);
        }
    }

    // load the upgrade lenUnit texture
    upgradeUnitTexture.loadFromFile("Game States/Pearl Shop/Upgrade Unit.png");
    upgradeHalfUnitTexture.loadFromFile("Game States/Pearl Shop/Upgrade Half Unit.png");

    loadStats();
}

void StateBestiary::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    titleText.update(window);
    backBtn.update(window);

    // update the textures
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if ((currPage * rows * cols) + (y * cols) + x < size(enemiesTextures)) {
                enemiesBtns[y * cols + x].rect.setTexture(&enemiesTextures[(currPage * rows * cols) + (y * cols) + x]);
                enemiesUnknowns[y * cols + x].rect.setTexture(&enemyUnknownTexture);
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
            case sf::Keyboard::M:
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

    else if (event.type == sf::Event::MouseButtonPressed) {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (enemiesBtns[y * cols + x].rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
                    (currPage * rows * cols) + (y * cols) + x < size(enemiesTextures)) {
                    currEnemy = (currPage * rows * cols) + (y * cols) + x;
                    loadStats();
                }
            }
        }

        if (backBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);
    }
}

void StateBestiary::loadStats() {
    // load the current enemy1 texture on the right box
    currEnemyBtn.rect.setTexture(&enemiesTextures[currEnemy]);

    auto enemy = Game::getInstance()->bestiary.beasts[currEnemy];
    units = {};
    int i;
    // health stats
    for (i = 0; i < floor(enemy.health); i++)
        units.push_back({upgradeUnitTexture, 0.025, {1410.0f + 55 * i, 450}});
    if (fmod(enemy.health, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {1410.0f + 55 * i - 12.5f, 450}});

    // speed stats
    for (i = 0; i < floor(enemy.speed); i++)
        units.push_back({upgradeUnitTexture, 0.025, {1410.0f + 55 * i, 570}});
    if (fmod(enemy.speed, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {1410.0f + 55 * i - 12.5f, 570}});

    // armor stats
    for (i = 0; i < floor(enemy.armor); i++)
        units.push_back({upgradeUnitTexture, 0.025, {1410.0f + 55 * i, 690}});
    if (fmod(enemy.armor, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {1410.0f + 55 * i - 12.5f, 690}});

    // strength stats
    for (i = 0; i < floor(enemy.strength); i++)
        units.push_back({upgradeUnitTexture, 0.025, {1410.0f + 55 * i, 810}});
    if (fmod(enemy.strength, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {1410.0f + 55 * i - 12.5f, 810}});
}

void StateBestiary::draw(sf::RenderWindow &window) {
    // draw the background and the title text
    window.draw(background);
    titleText.draw(window);
    backBtn.draw(window);

    // draw the enemies
    auto enemies = Game::getInstance()->bestiary.beasts;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            enemiesBtns[y * cols + x].draw(window);
            if ((currPage * rows * cols) + (y * cols) + x < size(enemies) &&
                !enemies[(currPage * rows * cols) + (y * cols) + x].discovered)
                enemiesUnknowns[y * cols + x].draw(window);
        }
    }
    // and the selected one
    currEnemyBtn.draw(window);

    // draw the stats upgrades
    for (int i = 0; i < size(units); i++)
        units[i].draw(window);

    // draw the stats icons
    healthIcon.draw(window);
    speedIcon.draw(window);
    armorIcon.draw(window);
    strengthIcon.draw(window);
}
