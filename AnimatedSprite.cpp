//
// Created by apisti01 on 10/07/22.
//

#include "AnimatedSprite.h"

void AnimatedSprite::move(float x, float y) {
    sprite.move(x,y);
}

AnimatedSprite::AnimatedSprite(sf::Texture &texture, sf::Vector2u imageCount) : frames(int(imageCount.x - 1)),
    rectangle(sf::IntRect(0, 0, int(texture.getSize().x / imageCount.x), int(texture.getSize().y / imageCount.y))) {
    sprite = sf::Sprite(texture,rectangle);
}

void AnimatedSprite::update(int frequency, int row) {
    rectangle.top = rectangle.height * row;

    if (clock.getElapsedTime().asMilliseconds() >= 1000/frequency){
        if(rectangle.left >= rectangle.width * frames){
            rectangle.left = 0;
        } else{
            rectangle.left += rectangle.width;
        }
        sprite.setTextureRect(rectangle);

        clock.restart();
    }
}

void AnimatedSprite::draw(sf::RenderWindow window) {
    window.draw(sprite);
}
