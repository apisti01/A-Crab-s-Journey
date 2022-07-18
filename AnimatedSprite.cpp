//
// Created by apisti01 on 10/07/22.
//

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const sf::Texture& texture, sf::Vector2u imageCount) : frames(int(imageCount.x - 1)),
    rectangle(sf::IntRect(0, 0, int(texture.getSize().x / imageCount.x), int(texture.getSize().y / imageCount.y))) {

    // initialize the sprite
    sprite = sf::Sprite(texture, rectangle);

    // set the origin in the middle to correct the rotation
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

    // rescale it
    sprite.setScale(scl, scl);
}

void AnimatedSprite::update(int frequency, int row, int deltaTime) {
    // choice of the row to determine the behaviour of the animation
    rectangle.top = rectangle.height * row;

    // increase of the time passed from last change of frame
    totalTime += deltaTime;

    // if it is time to switch frame
    if (totalTime >= pow(10, 6) / frequency) {
        // pass on the right frame or restart
        if (rectangle.left >= rectangle.width * frames) {
            rectangle.left = 0;
        } else {
            rectangle.left += rectangle.width;
        }
        sprite.setTextureRect(rectangle);

        // reset the time passed
        totalTime -= pow(10, 6) / frequency;
    }
}

void AnimatedSprite::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
