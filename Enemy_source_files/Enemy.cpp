//
// Created by apisti01 on 10/07/22.
//

#include "Enemy.h"
#include "../FloorMap.h"

Enemy::Enemy(std::string name, const sf::Texture& texture, Collider collider, std::unique_ptr<Weapon> weapon,
             float hp, float maxHp, float speed, float maxSpeed, float armor, float maxArmor, float strength,
             float maxStrength, float XpReward, int coinsDropped, int pearlsDropped) :
             GameCharacter(std::move(name), texture, std::move(collider), std::move(weapon), hp, maxHp, speed, maxSpeed, armor,
                           maxArmor, strength, maxStrength, sf::Vector2u(1,3)),
                           XpReward(XpReward),coinsDropped(coinsDropped), pearlsDropped(pearlsDropped) {

}

void Enemy::update(int deltaTime, FloorMap *floor, bool triggered) {

    float deltaAngle = 0;

    auto deltaPos = chase(floor->player.get(), deltaAngle, deltaTime, triggered);

    deltaPos = updateSpriteAndCollider(deltaPos, deltaAngle, floor);

    selectAnimation(deltaPos);

    // TODO forse non è necessario fare l'override della funzione attacco che è sempre la stessa
    //  (per ora la lascio, così è più semplice se vuoi fare modifiche al comportamento dell'attacco di ognuno)
    attack(floor, triggered);

    // update the animation
    sprite.update(fps, animationBehaviour, deltaTime);
}
