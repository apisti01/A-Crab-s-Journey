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
    // Destructor
    ~Game() = default;

    // getting one instance of the game, if it already exists it give the address of the one in use
    static Game* getInstance();

    // function that handle event and changes states
    void eventHandling(sf::Event event) { currentState->eventHandling(event); }

    // update the game on the different states it is
    void update(){ currentState->update();}

    // delegate to draw all
    void draw(sf::RenderWindow &window) { currentState->draw(window); }

    // restart the clock
    void restartClock() { gameClock.restart();}

    // changing the current state, creating a new one and deleting the old
    void changeState(StateType type);

    // pointer to the player, shared with the map
    std::shared_ptr<Player> player = nullptr;

    // pointer to the map
    std::unique_ptr<FloorMap> map = nullptr;

private:
    // private constructor to only have one instance of the class (Singleton)
    Game();

    // TODO all the increments and things to progress in the game

    // game instance
    static Game* gameInstance;

    // Current state of the game
    std::unique_ptr<State> currentState;

    // the clock to get delta time to move and update the game
    sf::Clock gameClock;

};


#endif //MAIN_CPP_GAME_H
