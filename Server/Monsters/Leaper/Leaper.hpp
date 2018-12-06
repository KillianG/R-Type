//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "AEnnemy.hpp"

class Leaper : public AEnnemy {
public:
    Leaper(EnnemyConfig::EnnemySpriteId id = EnnemyConfig::LEAPER, int hp = 1);

    MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

    std::vector<Game::ShootEvent> shootMissiles() override;

    virtual std::vector<Game::MonsterInfo> spawnEnnemies() override;

    const Game::vector2f &update(float) noexcept override;

protected:
    float _speedMonster { 300 };

    Game::vector2f _pos;
    Game::vector2f _dir { _speedMonster, _speedMonster };
};