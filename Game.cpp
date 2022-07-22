//
// Created by apisti01 on 18/07/22.
//

#include "Game.h"
#include "StateTitleScreen.h"
#include "StateMainMenu.h"
#include "StatePlay.h"

Game* Game::gameInstance = nullptr;

Game *Game::getInstance() {
    if (gameInstance == nullptr)
        gameInstance = new Game();
    return gameInstance;
}

Game::Game() : currentState(make_unique<StateTitleScreen>(this)) {
}

void Game::changeState(StateType type) {
    std::unique_ptr<State> tmp;
    // based on the enum it creates a new instance of a derived state class
    switch (type) { // FIXME to complete
        case StateType::MainMenu:
            tmp = std::make_unique<StateMainMenu>(this);
            break;
        case StateType::Play:
            tmp = std::make_unique<StatePlay>(this);
            break;
    }
    // the current state became the one just created, deleting the old one
    currentState = std::move(tmp);
}
