//
// Created by nhyarlathotep on 04/12/18.
//

#pragma once

#include "AEnnemy.hpp"

class Bird2 : public AEnnemy {
public:
    Bird2();

    MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

    bool shootMissile() noexcept override {
        return _isShooting;
    };

    std::vector<Game::ShootEvent> shootMissiles() override;

    virtual std::vector<Game::MonsterInfo> spawnEnnemies() override;

    const Game::vector2f &update(float) noexcept override;

private:
    bool _phase { true };
    float _speedMonster { 300 };

    Game::vector2f _pos;
    Game::vector2f _dir { _speedMonster, _speedMonster };
    float _basePosY { 0 };
    float _time;
    std::chrono::time_point<std::chrono::system_clock> _shootStart;
};