//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "AEnnemy.hpp"

class Meteorite : public AEnnemy {
public:
	Meteorite();

	MovableHitBox initEnnemy(const Game::vector2f &pos) noexcept override;

	std::vector<Game::ShootEvent> shootMissiles() override;

    std::vector<Game::MonsterInfo> spawnEnnemies() override;

	const Game::vector2f &update(float) noexcept override;

private:
	float _speedMonster { 100 };

	Game::vector2f _pos;
	Game::vector2f _dir { -_speedMonster, 0 };
};
