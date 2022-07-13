//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_ANIMATEDSPRITE_H
#define MAIN_CPP_ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>


class AnimatedSprite {
public:
    // Constructor and Destructor
    AnimatedSprite(const sf::Texture& texture, sf::Vector2u imageCount);
    ~AnimatedSprite() = default;

    // some getters and setters
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    float getWidth() const;
    float getHeight() const;

    // move across the map
    void move(float x, float y);

    // to change the angle the entity face
    void changeAngle(float angle);

    // function to update the sprite and to create the animation
    void update(int frequency, int row, int deltaTime);

    void draw(sf::RenderWindow &window);

private:

    sf::Sprite sprite;

    // time passed from the last change of frame of the animation
    int totalTime = 0;

    // the rectangle shown of the Sprite, the single frame in the sprite sheet
    sf::IntRect rectangle;

    // total of frames
    int frames;

};


#endif //MAIN_CPP_ANIMATEDSPRITE_H
