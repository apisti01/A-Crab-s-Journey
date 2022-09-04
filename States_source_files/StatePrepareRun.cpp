//
// Created by longo on 29/08/2022.
//

#include "StatePrepareRun.h"

StatePrepareRun::StatePrepareRun(Game *game) : State(game) {
    backgroundTexture.loadFromFile("Game States/Main Menu/Main Menu Blank.png");
}

void StatePrepareRun::update(int deltaTime, bool clicked, sf::RenderWindow &window) {
    startRunTextBtn.updateBtn(window);
    backBtn.updateBtn(window);
}

void StatePrepareRun::eventHandling(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonReleased) {
        // new game
        if (startRunTextBtn.btnText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            // create new floor
            setupPlayer(selectedCharacter);
            game->map = std::make_unique<FloorMap>(selectedCharacter, game->globalProgress.habitats[selectedMap].name,1);
            game->changeState(StateType::Play);
        }

        else if (backBtn.box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            game->changeState(StateType::MainMenu);
    }

    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        game->changeState(StateType::MainMenu);
}

void StatePrepareRun::draw(sf::RenderWindow &window) {
    // draw background
    window.draw(background);

    startRunTextBtn.drawTextBtn(window);

    backBtn.drawBtn(window);

}


void StatePrepareRun::setupPlayer(int characterIndex) {
    auto character = Game::getInstance()->globalProgress.characters[characterIndex];
    // load brown crab's texture for movement animation
    sf::Texture characterTexture;
    characterTexture.loadFromFile("GameCharacter/Player/" + character.name + "/Animations/Texture.png");

    // Ranged weapon
    std::unique_ptr<Weapon> rangedWeapon = std::make_unique<RangedWeapon>(RangedWeaponType::Rock,"carlo", 20);
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
    game->player = make_shared<Player>(characterIndex, "Crab", characterSpecie, std::move(characterTexture), collider,
                                 std::move(rangedWeapon), 10000, character.health, character.speed,
                                 character.speed, 100000, character.armor, 100000,
                                 character.strength); // FIXME to reset normal

    // and set his position at the center of the map
    game->player->setPosition(1920 / 2, 1080 / 2);
}