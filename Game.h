//
// Created by apisti01 on 18/07/22.
//

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include <memory>
#include <cfloat>
#include <cassert>

#include "Player.h"
#include "FloorMap.h"
#include "Bestiary.h"
#include "GlobalProgress.h"
#include "States_source_files/State.h"

class Game {
public:
    // Destructor
    ~Game() = default;

    // getting one instance of the game, if it already exists it give the address of the one in use
    static Game* getInstance();

    // function that handle event and changes states
    void eventHandling(sf::Event event, sf::RenderWindow &window) {
        currentState->eventHandling(event, window);
    }

    // changing the current state, creating a new one and deleting the old
    void changeState(StateType type);

    // update the game on the different states it is
    void update(int deltaTime, bool clicked, sf::RenderWindow &window) {
        currentState->update(deltaTime, clicked, window);
    }

    // delegate to draw all
    void draw(sf::RenderWindow &window) {
        currentState->draw(window);
    }

    void restartClock() {
        clock.restart();
    }

    void getMeasures(sf::RenderWindow &window);

    // pointer to the player, shared with the map
    std::shared_ptr<Player> player = nullptr;

    // pointer to the map
    std::unique_ptr<FloorMap> map;

    // Bestiary with the knowledge of all the enemy in the game
    Bestiary bestiary;

    // class that keeps track of the progress in the game,
    // used to prepare the single runs and to keep track of the upgrades bought
    GlobalProgress globalProgress;

    // the clock to get delta time to move and update the game
    sf::Clock clock;

    // font used in game
    sf::Font font;

    // screen and game measures
    int width, height, lenUnit;

private:
    // private constructor to only have one instance of the class (Singleton)
    Game();

    // game instance
    static Game* gameInstance;

    bool is_equal(float a, float b);

    // Current state of the game
    std::unique_ptr<State> currentState;
};


#endif //MAIN_CPP_GAME_H
