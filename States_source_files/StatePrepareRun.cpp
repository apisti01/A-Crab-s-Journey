//
// Created by longo on 29/08/2022.
//

#include "StatePrepareRun.h"

StatePrepareRun::StatePrepareRun(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");

    sf::Texture texture;
    // load the characters textures
    /*
    auto characters = game->globalProgress.characters;
    for (int i = 0; i < size(characters); i++) {
        texture.loadFromFile("Game States/Prepare Run/" + characters[i].name + ".png");
        charactersTextures.push_back(texture);
    }*/
    texture.loadFromFile("Game States/Prepare Run/BrownCrab.png");
    charactersTextures.push_back(texture);

    // and the maps textures
    /*
    auto habitats = game->globalProgress.habitats;
    for (int i = 0; i < size(habitats); i++) {
        texture.loadFromFile("Game States/Prepare Run/" + habitats[i].name + ".png");
        mapsTextures.push_back(texture);
    }*/
    texture.loadFromFile("Game States/Prepare Run/CoralReef.png");
    mapsTextures.push_back(texture);
}

void StatePrepareRun::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    // update the textures
    currCharacter.rect.setTexture(&charactersTextures[currCharacterIndex]);
    currMap.rect.setTexture(&mapsTextures[currMapIndex]);

    // the next and prev buttons
    nextCharacterBtn.update(window);
    prevCharacterBtn.update(window);
    nextMapBtn.update(window);
    prevMapBtn.update(window);

    // the "start run" button
    startRunTextBtn.update(window);

    // and the "go back" button
    backBtn.update(window);
}

void StatePrepareRun::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        // if the selected character and map are unlocked
        if (startRunTextBtn.text.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) &&
            game->getInstance()->globalProgress.characters[currCharacterIndex].unlocked &&
            game->getInstance()->globalProgress.habitats[currMapIndex].unlocked) {
            // create new floor
            setupPlayer(currCharacterIndex);
            game->map = std::make_unique<FloorMap>(currCharacterIndex, game->globalProgress.habitats[currMapIndex].name, 1);
            game->changeState(StateType::Play);
        }

        else if (nextCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            currCharacterIndex = (currCharacterIndex + 1) % size(charactersTextures);

        else if (prevCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            currCharacterIndex = (currCharacterIndex + size(charactersTextures) - 1) % size(charactersTextures);

        else if (nextCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            currMapIndex = (currMapIndex + 1) % size(mapsTextures);

        else if (nextCharacterBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            currMapIndex = (currMapIndex + size(mapsTextures) - 1) % size(mapsTextures);

        else if (backBtn.rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);
    }

    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::MainMenu);
}

void StatePrepareRun::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    currMap.draw(window);
    nextMapBtn.draw(window);
    prevMapBtn.draw(window);

    currCharacter.draw(window);
    nextCharacterBtn.draw(window);
    prevCharacterBtn.draw(window);

    // if the selected character and map are unlocked the text is available to be clicked, otherwise is not
    if (game->getInstance()->globalProgress.characters[currCharacterIndex].unlocked &&
        game->getInstance()->globalProgress.habitats[currMapIndex].unlocked)
        startRunTextBtn.draw(window);

    backBtn.draw(window);
}


void StatePrepareRun::setupPlayer(int characterIndex) {
    auto character = Game::getInstance()->globalProgress.characters[characterIndex];
    // load brown crab's texture for movement animation
    sf::Texture characterTexture;
    characterTexture.loadFromFile("GameCharacter/Player/" + character.name + "/Animations/Texture.png");

    // Ranged weapon
    std::unique_ptr<Weapon> rangedWeapon = std::make_unique<RangedWeapon>(RangedWeaponType::Rock, "Rock", 20);
    // give him a melee weapon
    // std::unique_ptr<Weapon> weapon = std::make_unique<MeleeWeapon>(10, "player", ItemRarity::Common, 50);

    // and a collider
    Collider collider(float(1920) / 2, float(1080) / 2,
                      characterTexture.getSize().x / 6 * 0.4 * 0.6,
                      characterTexture.getSize().y / 3 * 0.4 * 0.8);

    CrabSpecie characterSpecie;
    if (character.name == "BrownCrab")
        characterSpecie = CrabSpecie::BrownCrab;
    else if (character.name == "FiddlerCrab")
        characterSpecie = CrabSpecie::FiddlerCrab;
    else if (character.name == "TriangleTannerCrab")
        characterSpecie = CrabSpecie::TriangleTannerCrab;
    else if (character.name == "AsianGreatPaddle")
        characterSpecie = CrabSpecie::AsianGreatPaddle;

    // create the player
    game->player = make_shared<Player>(characterIndex, character.name, characterSpecie, std::move(characterTexture),
                                       collider, std::move(rangedWeapon),
                                       character.health + character.healthUpgrades / 2,
                                       character.health + character.healthUpgrades / 2,
                                       character.speed + character.speedUpgrades / 2,
                                       character.speed + character.speedUpgrades / 2,
                                       character.armor + character.armorUpgrades / 2,
                                       character.armor + character.armorUpgrades / 2,
                                       character.strength + character.strengthUpgrades / 2,
                                       character.strength + character.strengthUpgrades / 2);

    // and set his position at the center of the map
    game->player->setPosition(1920 / 2, 1080 / 2);
}