//
// Created by apisti01 on 13/07/22.
//

#ifndef MAIN_CPP_STATICRANGEDENEMY_H
#define MAIN_CPP_STATICRANGEDENEMY_H

#include "Enemy.h"

class StaticRangedEnemy : Enemy{
public:
    StaticRangedEnemy();
    ~StaticRangedEnemy() override = default;

    void chase(const Player &hero) override;

    void dropItems() override;

private:


};


#endif //MAIN_CPP_STATICRANGEDENEMY_H
