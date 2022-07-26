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
    PrepareRun,
    Play,
    ManageInventory,
    DisplayMap,
    Shop,
    Pause,
    PearlShop,
    Settings,
    Credits
};

class State {
public:
    // Constructor and Destructor
    explicit State(Game* game) : game(game) {}
    virtual ~State() = default;

    // to handle the event as changing of the  current state
    virtual void eventHandling(sf::Event event, sf::RenderWindow &window) = 0;

    // updating all the game
    virtual void update(int deltaTime, bool clicked) = 0;

    // drawing the next frame on the window
    virtual void draw(sf::RenderWindow &window) = 0;

protected:
    // pointer to the game class
    Game* game;
};


#endif //MAIN_CPP_STATE_H
