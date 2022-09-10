//
// Created by apisti01 on 18/07/22.
//

#include "Game.h"
#include "States_source_files/StateTitleScreen.h"
#include "States_source_files/StateMainMenu.h"
#include "States_source_files/StatePearlShop.h"
#include "States_source_files/StatePrepareRun.h"
#include "States_source_files/StatePlay.h"
#include "States_source_files/StateDisplayMap.h"
#include "States_source_files/StateManageInventory.h"
#include "States_source_files/StateShop.h"
#include "States_source_files/StatePause.h"
#include "States_source_files/StateBestiary.h"
#include "States_source_files/StateGameOver.h"
#include "States_source_files/StateSettings.h"

#include <iostream>

Game* Game::gameInstance = nullptr;

Game* Game::getInstance() {
    if (gameInstance == nullptr)
        gameInstance = new Game();
    return gameInstance;
}

Game::Game() : currentState(make_unique<StateTitleScreen>(this)), bestiary(Bestiary()), globalProgress(GlobalProgress()) {
    // load font
    sf::Font Rancho;
    if (!Rancho.loadFromFile("Assets/Font/Rancho/Rancho.ttf")) {
        cout << "font non caricato" << endl;
        system("pause");
    }
    font = Rancho;
}

void Game::getMeasures(sf::RenderWindow &window) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

    if (is_equal(aspectRatio, 16.0 / 9.0) ||
        is_equal(aspectRatio, 16.0 / 10.0) ||
        is_equal(aspectRatio, 4.0 / 3.0))
        lenUnit = floor(window.getSize().x / 16.0);
    else if (is_equal(aspectRatio, 5.0 / 4.0))
        lenUnit = floor(window.getSize().x / 15.0);
    else if (is_equal(aspectRatio, 21.0 / 9.0))
        lenUnit = floor(window.getSize().x / 21.0);

    cout << lenUnit << endl;

    width = window.getSize().x;
    height = window.getSize().y;
}

void Game::changeState(StateType type) {
    std::unique_ptr<State> tmp;

    try {
        // FIXME to complete
        // based on the enum it creates a new instance of a derived state class
        switch (type) {
            case StateType::MainMenu:
                tmp = std::make_unique<StateMainMenu>(this);
                break;
            case StateType::PearlShop:
                tmp = std::make_unique<StatePearlShop>(this);
                break;
            case StateType::PrepareRun:
                tmp = std::make_unique<StatePrepareRun>(this);
                break;
            case StateType::Play:
                tmp = std::make_unique<StatePlay>(this);
                break;
            case StateType::DisplayMap:
                tmp = std::make_unique<StateDisplayMap>(this);
                break;
            case StateType::ManageInventory:
                tmp = std::make_unique<StateManageInventory>(this);
                break;
            case StateType::Shop:
                tmp = std::make_unique<StateShop>(this);
                break;
            case StateType::Bestiary:
                tmp = std::make_unique<StateBestiary>(this);
                break;
            case StateType::Pause:
                tmp = std::make_unique<StatePause>(this);
                break;
            case StateType::GameOver:
                tmp = std::make_unique<StateGameOver>(this);
                break;
            case StateType::Settings:
                tmp = std::make_unique<StateSettings>(this);
                break;
        }
    } catch (exception &e) {
        std::cout << e.what();
    }

    // the current state became the one just created, deleting the old one
    currentState = std::move(tmp);
}

bool Game::is_equal(float a, float b) {
    return fabs(a - b) <= 0.01;
}
