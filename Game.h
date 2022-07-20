//
// Created by apisti01 on 18/07/22.
//

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include <memory>

#include "Player.h"
#include "FloorMap.h"
#include "State.h"


class Game {
public:
    // Constructor and Destructor

    ~Game() = default;

    static Game* getInstance();



    // delegate to draw all
    void draw(sf::RenderWindow window){ currentState->draw(window); }


private:
    // TODO all the increments and things to progress in the game

    // game instance
    static Game* gameInstance;

    // pointer to the player, shared with the map
    std::shared_ptr<Player> player = nullptr;

    // pointer to the map
    std::unique_ptr<FloorMap> map = nullptr;

    // Current state of the game
    std::unique_ptr<State> currentState;

};


#endif //MAIN_CPP_GAME_H
