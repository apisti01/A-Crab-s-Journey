//
// Created by apisti01 on 09/07/22.
//

#include "Bullet.h"

Bullet::Bullet(float damage, float speed, float range, sf::Sprite body, bool isTracking, bool isShattering)
                : damage(damage), speed(speed), range(range), body(std::move(body)), isShattering(isShattering), isTracking(isTracking){

}
