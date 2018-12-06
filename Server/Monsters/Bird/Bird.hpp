//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "AEnnemy.hpp"

class Bird : public AEnnemy {
public:
    Bird();

    MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

    std::vector<Game::ShootEvent> shootMissiles() override;

    virtual std::vector<Game::MonsterInfo> spawnEnnemies() override;

    const Game::vector2f &update(float) noexcept override;

private:
    bool _phase { true };
    float _speedMonster { 300 };

    Game::vector2f _pos;
    Game::vector2f _dir { _speedMonster, _speedMonster };
    float _basePosY { 0 };
};