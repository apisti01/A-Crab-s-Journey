//
// Created by apisti01 on 10/07/22.
//

#ifndef MAIN_CPP_ANIMATEDSPRITE_H
#define MAIN_CPP_ANIMATEDSPRITE_H

#include <SFML/Graphics.hpp>
#include <cmath>


class AnimatedSprite {
public:
    // Constructor and Destructor
    AnimatedSprite(const sf::Texture& texture, sf::Vector2u imageCount);
    ~AnimatedSprite() = default;

    // getter and setter for sprite position
    void setPosition(sf::Vector2f position) { sprite.setPosition(position); }
    sf::Vector2f getPosition() const { return sprite.getPosition(); }

    // getter for sprite size
    float getWidth() const { return sprite.getGlobalBounds().width; }
    float getHeight() const { return sprite.getGlobalBounds().height; }

    // move across the map
    void move(float x, float y) { sprite.move(x, y); }

    // getter and setter for the angle
    void setAngle(float angle) {
        // angle conversion: radians -> degrees
        angle = angle * 180 / M_PI;
        // adjustment for SFML plane
        angle += 90;

        sprite.setRotation(angle);
    }
    float getAngle() {
        float angle = sprite.getRotation();

        // adjustment for SFML plane
        angle -= 90;
        // angle conversion: degrees -> radians
        angle = angle * M_PI / 180;

        return angle;
    }

    // function to update the sprite and to create the animation
    void update(int frequency, int row, int deltaTime);

    void draw(sf::RenderWindow &window);

private:
    sf::Texture characterTexture;
    sf::Sprite sprite;
    float scl = 0.4;

    // time passed from the last change of frame of the animation
    int totalTime = 0;

    // the rectangle shown of the Sprite, the single frame in the sprite sheet
    sf::IntRect rectangle;

    // total of frames
    int frames;
};


#endif //MAIN_CPP_ANIMATEDSPRITE_H
