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
	int width;
	int height;
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
		missileSpeed = { 650 };

		_60fps = { std::chrono::nanoseconds(16666666) };
		_120fps = { std::chrono::nanoseconds(8333333) };

		playerHitBox = { 66, 34 };
		missileHitBoxes = { {{ 17, 12 }, { 33, 12 }, { 49, 14 }, { 65, 14 }, { 81, 16 }}};

		allEntityInit = {
				{0, "bg_dullstars", 1280, 720}, /* Backgrounds bg_darknebula */
				{1, "player1", 66, 34}, /* Player */
				{2, "player2", 66, 34}, /* Player */
				{3, "player3", 66, 34}, /* Player */
				{4, "player4", 66, 34}, /* Player */

				{5, "missile1", 34, 24}, /* Missile */
				{6, "missile2", 66, 26}, /* Missile */
				{7, "missile3", 98, 28}, /* Missile */
				{8, "missile4", 130, 28}, /* Missile */
				{9, "missile5", 162, 32}, /* Missile */
				{10, "ennemyMissile0_17x14", 34, 28}, /* Missile */

                {11, "planet_sun1", 1000, 1000}, /* Backgrounds */
                {12, "planet_populated_brown", 512, 512}, /* Backgrounds */
                {13, "StarField", 544, 320}, /* Backgrounds */

				{14, "bonus1", 34, 36}, /* SpeedUp */
				{15, "bonus2", 34, 36}, /* Shield bonus */
				{16, "Shield", 80, 50} /* Shield */
		};

		auto &loader = gfx::Singleton<game::DynamicLoaderManager>::get();
		loader.loadLibs();
		auto init = loader.getInit();
		allEntityInit.insert(allEntityInit.end(), init.begin(), init.end());
	}
}
