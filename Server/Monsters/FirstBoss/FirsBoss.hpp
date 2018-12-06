//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "AEnnemy.hpp"

class FirstBoss : public AEnnemy {
public:
    FirstBoss();

    MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

    std::vector<Game::ShootEvent> shootMissiles() override;

    std::vector<Game::MonsterInfo> spawnEnnemies() override;

    const Game::vector2f &update(float) noexcept override;

private:
	float _time { 0 };
	float _burstcoolDownTime { 2.5 };
	static constexpr float _speedMonster { 240 };
    static constexpr float _speedMissile { 500 };

	Game::vector2f _pos;
    Game::vector2f _angles { 120, 240 };
	Game::vector2f _dir { -_speedMonster, _speedMonster };
};

