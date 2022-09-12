//
// Created by apisti01 on 10/07/22.
//

#include "Enemy.h"
#include "../FloorMap.h"

Enemy::Enemy(int id, std::string name, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
             float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
             float maxStrength, float XpReward, int coinsDropped, int pearlsDropped, int attackTimer, float units) :
             GameCharacter(std::move(name), texture, std::move(collider), std::move(weapon), hp, maxHp, speed, maxSpeed, armor,
                           maxArmor, strength, maxStrength, sf::Vector2u(1, 1), units), id(id),
                           XpReward(XpReward), coinsDropped(coinsDropped), pearlsDropped(pearlsDropped), clock(0),
                           attackTimer(attackTimer * pow(10, 6)) {
}

void Enemy::update(int deltaTime, FloorMap *floor, bool triggered, sf::RenderWindow &window) {
    clock += deltaTime;

    float deltaAngle = 0;

    sf::Vector2f deltaPos = chase(floor->player.get(), deltaAngle, deltaTime, triggered);

    updateColliderAndSprite(deltaPos, deltaAngle, floor);

    // TODO: aggiungere le altre animazioni per i nemici e reinserire la funzione di selezione
    // selectAnimation();

    // TODO: forse non è necessario fare l'override della funzione attacco che è sempre la stessa
    //       (per ora la lascio, così è più semplice se vuoi fare modifiche al comportamento dell'attacco di ognuno)
    if (clock >= attackTimer) {
        clock -= attackTimer;
        attack(floor, triggered);
    }

    // update the animation
    sprite.update(fps, animationBehaviour, deltaTime);
}
