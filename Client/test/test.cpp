/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <Client/MainMenu/Settings.hpp>
#include "catch.hpp"


TEST_CASE("Settings", "[Settings]") {

	SECTION("Getters") {

		Settings settings;

		REQUIRE(settings.downKey == "S");
		REQUIRE(settings.leftKey == "Q");
		REQUIRE(settings.rightKey == "D");
		REQUIRE(settings.shootKey == "Space");
		REQUIRE(settings.upKey == "Z");
		REQUIRE(settings.volume == 0.5);





	}

	SECTION("Setters") {
		Settings settings;

		settings.downKey = "P";
		REQUIRE(settings.downKey == "P");

		settings.leftKey = "L";
		REQUIRE(settings.leftKey == "L");

		settings.rightKey = "R";
		REQUIRE(settings.rightKey == "R");

		settings.shootKey = "K";
		REQUIRE(settings.shootKey == "K");

		settings.upKey = "U";
		REQUIRE(settings.upKey == "U");


	}
}