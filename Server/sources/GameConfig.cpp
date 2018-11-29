/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <array>
#include "Server/includes/DynamicLoaderManager.hpp"
#include "../../libs/GFX/Singleton.hpp"
#include "GameConfig.hpp"
#include "networkUtils.hpp"
#include "Utils.hpp"

namespace Config {
	uint32_t width;
	uint32_t height;
	float speed;
	float missileSpeed;

    std::chrono::nanoseconds _60fps;
    std::chrono::nanoseconds _120fps;

	Game::box playerHitBox;
	std::vector<Game::box> missileHitBoxes;
	std::vector<network::EntityInfo> allEntityInit;

	/**
	 * Init all global
	 */
	void initConfig()
	{
		width  = { 1280 };
		height = { 720 };
		speed = { 300 };
		missileSpeed = { 450 };

		_60fps = { std::chrono::nanoseconds(16666666) };
		_120fps = { std::chrono::nanoseconds(8333333) };

		playerHitBox = { 66, 34 };

		missileHitBoxes = { {{ 17, 12 }, { 33, 12 }, { 49, 14 }, { 65, 14 }, { 81, 16 }}};

		allEntityInit = {
		{0, "background", 0 ,0}, /* Background */
        {1, "player1", 66, 34}, /* Player */
        {2, "player2", 66, 34}, /* Player */
        {3, "player3", 66, 34}, /* Player */
        {4, "player4", 66, 34}, /* Player */

        {5, "missile1_17x12", 17, 12}, /* Missile */
        {6, "missile2_33x12", 33, 12}, /* Missile */
        {7, "missile3_49x14", 49, 14}, /* Missile */
        {8, "missile4_65x14", 65, 14}, /* Missile */
        {9, "missile5_81x16", 81, 16}, /* Missile */
		};

		auto &loader = gfx::Singleton<game::DynamicLoaderManager>::get();
		loader.loadLibs();
		auto init = loader.getInit();
		allEntityInit.insert(allEntityInit.end(), init.begin(), init.end());
	}
}
