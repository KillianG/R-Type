/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <thread>
#include "Server.hpp"
#include "catch.hpp"

TEST_CASE("GAME CORE TEST", "[SERVER]")
{
	std::string local("127.0.0.1");
	std::string login1("Erwan");
	network::UdpSocket client1(50004);
	network::UdpSocket client2(50005);
	network::MyRfcClient<network::UdpSocket> rfcC1(client1);
	network::MyRfcClient<network::UdpSocket> rfcC2(client2);

	EventManager evt;
	std::shared_ptr<network::UdpSocket> gameSocket;

	gameSocket = std::make_shared<network::UdpSocket>(50006);
	Game::GameEngine gameCore(gameSocket);
	SECTION("GAME CORE CONNECTION")
	{
		std::thread tCore(&Game::GameEngine::run, &gameCore);
		REQUIRE_NOTHROW(rfcC1.FirstConnectToGame(local, 50006, login1));
		REQUIRE(rfcC1.isGameConnected());

		gameCore.stopGame();
		tCore.join();
	}
}

