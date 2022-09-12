//
// Created by longo on 19/08/2022.
//

#include "StateBestiary.h"

StateBestiary::StateBestiary(Game *game) : State(game) {
    auto enemies = Game::getInstance()->bestiary.beasts;
    for (int i = 0; i < size(enemies); i++) {
        // load the enemies textures
        enemiesTextures.emplace_back();
        enemiesTextures[i].loadFromFile(
                "Assets/GameCharacter/Enemy/" + enemies[i].type + "/" + enemies[i].name + "/Texture.png");
    }

    // load the enemy unknown texture
    int posX, posY;
    enemyUnknownTexture.loadFromFile("Assets/GameCharacter/Enemy/Unknown Enemy.png");
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            SpriteButton enemy = {"Assets/GameCharacter/Enemy/AggressiveMelee/SeaTurtle/Texture.png", 0.09,
                            {.11f + x * .125f, .36f + y * .22f}, false};
            enemiesBtns.push_back(enemy);

            SpriteButton enemyUnknown = {"Assets/GameCharacter/Enemy/Unknown Enemy.png", 0.09,
                                   {.11f + x * .125f, .36f + y * .22f}, false};
            enemiesUnknowns.push_back(enemyUnknown);
        }
    }

    // load the upgrade lenUnit texture
    upgradeUnitTexture.loadFromFile("Assets/GameStates/PearlShop/Upgrade Unit.png");
    upgradeHalfUnitTexture.loadFromFile("Assets/GameStates/PearlShop/Upgrade Half Unit.png");

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
        units.push_back({upgradeUnitTexture, 0.025, {.73f + .028f * i, .41f}});
    if (fmod(enemy.health, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {.73f + .028f * i - .007f, .41f}});

    // speed stats
    for (i = 0; i < floor(enemy.speed); i++)
        units.push_back({upgradeUnitTexture, 0.025, {.73f + .028f * i, .52f}});
    if (fmod(enemy.speed, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {.73f + .028f * i - .007f, .52f}});

    // armor stats
    for (i = 0; i < floor(enemy.armor); i++)
        units.push_back({upgradeUnitTexture, 0.025, {.73f + .028f * i, .64f}});
    if (fmod(enemy.armor, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {.73f + .028f * i - .007f, .64f}});

    // strength stats
    for (i = 0; i < floor(enemy.strength); i++)
        units.push_back({upgradeUnitTexture, 0.025, {.73f + .028f * i, .75f}});
    if (fmod(enemy.strength, 1) != 0)
        units.push_back({upgradeHalfUnitTexture, 0.025, {.73f + .028f * i - .007f, .75f}});
}

void StateBestiary::draw(sf::RenderWindow &window) {
    // draw the background and the title text
    background.draw(window);
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
