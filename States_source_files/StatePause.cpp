//
// Created by longo on 24/07/2022.
//

#include "StatePause.h"
#include "../Game.h"

StatePause::StatePause(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Games States/Pause Screen/Pause Screen Blank.png");

    resumeBtnTexture.loadFromFile("Games States/Pause Screen/Resume Texture.png");
    float resumeBtnScl = 0.8;
    resumeBtn.setPosition(1920 / 2, 300);
    resumeBtn.setScale(resumeBtnScl, resumeBtnScl);
    resumeBtn.setOrigin(resumeBtnTexture.getSize().x / 2, resumeBtnTexture.getSize().y / 2);
    resumeBtn.setSize(sf::Vector2f(resumeBtnTexture.getSize().x, resumeBtnTexture.getSize().y));
    resumeBtn.setTexture(&resumeBtnTexture);

    exitBtnTexture.loadFromFile("Games States/Pause Screen/Exit Texture.png");
    float exitBtnScl = 0.8;
    exitBtn.setPosition(1920 / 2, 500);
    exitBtn.setScale(exitBtnScl, exitBtnScl);
    exitBtn.setOrigin(exitBtnTexture.getSize().x / 2, exitBtnTexture.getSize().y / 2);
    exitBtn.setSize(sf::Vector2f(exitBtnTexture.getSize().x, exitBtnTexture.getSize().y));
    exitBtn.setTexture(&exitBtnTexture);

    settingsBtnTexture.loadFromFile("Games States/Pause Screen/Settings Texture.png");
    float settingsBtnScl = 0.8;
    settingsBtn.setPosition(1920 / 2, 700);
    settingsBtn.setScale(settingsBtnScl, settingsBtnScl);
    settingsBtn.setOrigin(settingsBtnTexture.getSize().x / 2, settingsBtnTexture.getSize().y / 2);
    settingsBtn.setSize(sf::Vector2f(settingsBtnTexture.getSize().x, settingsBtnTexture.getSize().y));
    settingsBtn.setTexture(&settingsBtnTexture);
}

void StatePause::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::Play);

    if (event.type == sf::Event::MouseButtonReleased) {
        if (resumeBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Play);

        if (exitBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);

        if (settingsBtn.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::Settings);
    }
}

void StatePause::draw(sf::RenderWindow &window) {
    // draw the background
    window.draw(background);

    // and all the buttons
    window.draw(resumeBtn);
    window.draw(exitBtn);
    window.draw(settingsBtn);
}
