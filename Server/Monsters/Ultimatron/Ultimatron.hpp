//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "AEnnemy.hpp"

class Ultimatron : public AEnnemy {
public:
    Ultimatron();

    MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

    bool shootMissile() noexcept override;

    std::vector<Game::ShootEvent> shootMissiles() override;

    std::vector<Game::MonsterInfo> spawnEnnemies() override;

    const Game::vector2f &update(float) noexcept override;

private:
    std::vector<Game::ShootEvent> partern1();
    std::vector<Game::ShootEvent> partern2();
    std::vector<Game::ShootEvent> partern3();

private:
    float _time { 1 };
    float _coolDownTime { 0.08 };
    float _BurstcoolDownTime { 3 };
    float _timeSinceLastFrame { 0 };

    int _choice { 0 };
    Game::vector2f _pos;
    static constexpr float _speedMissile { 500 };
};