//
// Created by nhyarlathotep on 24/11/18.
//

#pragma once

#include <vector>
#include "Utils.hpp"
#include "../../libs/Network/networkUtils.hpp"

namespace Config {
	extern uint32_t width;
	extern uint32_t height;
	extern float speed;
	extern float missileSpeed;

    extern std::chrono::nanoseconds _60fps;
    extern std::chrono::nanoseconds _120fps;

	extern Game::box playerHitBox;
	extern std::vector<Game::box> missileHitBoxes;
	extern std::vector<network::EntityInfo> allEntityInit;

	void initConfig();
}
