//
// Created by apisti01 on 19/07/22.
//

#ifndef MAIN_CPP_STATE_H
#define MAIN_CPP_STATE_H

#include <SFML/Graphics.hpp>

class State {
public:


    virtual void draw(sf::RenderWindow &window) = 0;

private:

};


#endif //MAIN_CPP_STATE_H
