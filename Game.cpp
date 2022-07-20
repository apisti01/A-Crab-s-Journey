//
// Created by apisti01 on 18/07/22.
//

#include "Game.h"

Game* Game::gameInstance = nullptr;

Game *Game::getInstance() {
    if (gameInstance == nullptr)
        gameInstance = new Game;
    return gameInstance;
}
