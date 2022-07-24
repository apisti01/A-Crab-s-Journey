//
// Created by apisti01 on 18/07/22.
//

#include "Game.h"
#include "StateTitleScreen.h"
#include "StateMainMenu.h"
#include "StatePlay.h"
#include "StateDisplayMap.h"

#include <iostream>

Game* Game::gameInstance = nullptr;

Game *Game::getInstance() {
    if (gameInstance == nullptr)
        gameInstance = new Game();
    return gameInstance;
}

Game::Game() : currentState(make_unique<StateTitleScreen>(this)) {}

void Game::changeState(StateType type) {
    std::unique_ptr<State> tmp;

    // FIXME to complete
    // based on the enum it creates a new instance of a derived state class
    switch (type) {
        case StateType::MainMenu:
            tmp = std::make_unique<StateMainMenu>(this);
            break;
        case StateType::Play: {
            // FIXME: move to another place
            // create new floor
            int level = 1;
            map = std::make_unique<FloorMap>(level, MapType::CoralReef);

            tmp = std::make_unique<StatePlay>(this);
        }
            break;
        case StateType::DisplayMap:
            tmp = std::make_unique<StateDisplayMap>(this);
            break;
    }
    // the current state became the one just created, deleting the old one
    currentState = std::move(tmp);
}
