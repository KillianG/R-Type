//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "IEnnemy.hpp"

class Bird2 : public IEnnemy {
public:
    Bird2() = default;

    MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

    const Game::vector2f &move(float) noexcept override;

private:
    bool _phase { true };
    float _speedMonster { 300};

    Game::vector2f _pos;
    Game::vector2f _dir { -_speedMonster, 0 };
};

