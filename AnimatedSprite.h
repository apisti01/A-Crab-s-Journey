//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_ANIMATEDSPRITE_H
#define MAIN_CPP_ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>


class AnimatedSprite {
public:
    // Constructor and Destructor
    AnimatedSprite(sf::Texture &texture, sf::Vector2u imageCount);
    ~AnimatedSprite() = default;

    // move across the map
    void move(float x, float y);

    // function to update the sprite and to create the animation
    void update(int frequency, int row);

    void draw(sf::RenderWindow window);

private:
    sf::Sprite sprite;

    sf::Clock clock;

    // the rectangle shown of the Sprite, the single frame in the sprite sheet
    sf::IntRect rectangle;

    // total of frames
    int frames;

};


#endif //MAIN_CPP_ANIMATEDSPRITE_H
