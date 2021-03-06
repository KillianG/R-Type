//
// Created by nhyarlathotep on 04/12/18.
//

#pragma once

#include "AEnnemy.hpp"

class Bird3 : public AEnnemy {
public:
    Bird3();

    MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

    bool shootMissile() noexcept override;

    std::vector<Game::ShootEvent> shootMissiles() override;

    virtual std::vector<Game::MonsterInfo> spawnEnnemies() override;

    const Game::vector2f &update(float) noexcept override;

private:
    float _coolDownTime { 0.1 };
    float _timeSinceLastFrame { 0 };
    static constexpr float _speedMonster { 350 };
    static constexpr float  _speedMissile { 500 };

    Game::vector2f _pos;
    Game::vector2f _dir { _speedMonster, 0 };
};