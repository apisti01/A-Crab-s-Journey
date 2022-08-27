//
// Created by longo on 24/07/2022.
//

#include "StatePause.h"
#include "../Game.h"

StatePause::StatePause(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Pause Screen/Pause Screen Blank.png");

    resumeBtnTexture.loadFromFile("Games States/Pause Screen/Resume Texture.png");
    createStateButton(&resumeBtn, resumeBtnTexture, 0.8, 1920 / 2, 300);
    resumeBtn.setTexture(&resumeBtnTexture);

    exitBtnTexture.loadFromFile("Games States/Pause Screen/Exit Texture.png");
    createStateButton(&exitBtn, exitBtnTexture, 0.8, 1920 / 2, 500);
    exitBtn.setTexture(&exitBtnTexture);

    settingsBtnTexture.loadFromFile("Games States/Pause Screen/Settings Texture.png");
    createStateButton(&settingsBtn, settingsBtnTexture, 0.8, 1920 / 2, 700);
    settingsBtn.setTexture(&settingsBtnTexture);
}

void StatePause::createStateButton(sf::RectangleShape* btn, sf::Texture btnTexture, float scl, float posX, float posY, bool clickable) {
    btn->setPosition(posX, posY);
    btn->setScale(scl, scl);
    btn->setOrigin(btnTexture.getSize().x / 2, btnTexture.getSize().y / 2);
    btn->setSize(sf::Vector2f(btnTexture.getSize().x, btnTexture.getSize().y));
    if (clickable)
        btn->setFillColor(sf::Color(255, 255, 255, 128));
}

void StatePause::eventHandling(sf::Event event, sf::RenderWindow &window) {
    updateButton(&resumeBtn, window);
    updateButton(&exitBtn, window);
    updateButton(&settingsBtn, window);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Play);

    else if (event.type == sf::Event::MouseButtonReleased) {
        if (resumeBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);

        else if (exitBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);

        else if (settingsBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StatePause::updateButton(sf::RectangleShape* btn, sf::RenderWindow &window) {
    // TODO: create button class
    if (btn->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        btn->setFillColor(sf::Color(255, 255, 255, 255));
    else
        btn->setFillColor(sf::Color(255, 255, 255, 128));
}

void StatePause::draw(sf::RenderWindow &window) {
    // draw the background
    window.draw(background);

    // and all the buttons
    window.draw(resumeBtn);
    window.draw(exitBtn);
    window.draw(settingsBtn);
}
