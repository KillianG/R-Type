/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "catch.hpp"
#include <unistd.h>
#include "Server/levelParsing/ParsingLevel.hpp"

TEST_CASE("SERVER PARSING LEVEL", "[SERVER]")
{
	SECTION("SERVER PARSING")
	{
		Game::ParsingLevel parsing;

		REQUIRE_THROWS_AS(parsing.getMonster(0), rtype::Exception);

		parsing.startGame();
		usleep(1000);
		std::vector<Game::MonsterInfo> monsterList = parsing.getMonster(1000);
		usleep(1000);
		usleep(1000);
		usleep(1000);
		monsterList = parsing.getMonster(3000);
		monsterList = parsing.getMonster(3000);
	}
}
