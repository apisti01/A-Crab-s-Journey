//
// Created by apisti01 on 19/07/22.
//

#ifndef MAIN_CPP_STATE_H
#define MAIN_CPP_STATE_H

#include <SFML/Graphics.hpp>

class Game;

enum class StateType{
    TitleScreen,
    MainMenu,
    Pause,
    Play,
    DisplayMap,
    Shop,
    ManageInventory
};

class State {
public:
    // Constructor and Destructor
    explicit State(Game* game) : game(game){}
    virtual ~State() = default;

    // to handle the event as changing of the  current state
    virtual void eventHandling(sf::Event event) = 0;

    // updating all the game
    virtual void update() = 0;

    // drawing the next frame on the window
    virtual void draw(sf::RenderWindow &window) = 0;

protected:
    // pointer to the game class
    Game* game;

};


#endif //MAIN_CPP_STATE_H
