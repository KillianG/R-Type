/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <thread>
#include "Server.hpp"
#include "catch.hpp"

TEST_CASE("SERVER CONNECTION", "[SERVER]")
{
	std::string ip("127.0.0.1");
	std::string gameName("GAME 1");
	std::string gameName2("GAME 2");
	std::string login1("Erwan");
	std::string login2("Rudy");
	rtype::Server serv;

	network::TcpManager client1(5004);
	network::TcpManager client2(5005);
	network::MyRfcClient<network::TcpManager> rfcClient1(client1);
	network::MyRfcClient<network::TcpManager> rfcClient2(client2);

	SECTION("SERVER CONNECTION")
	{
		std::thread t(&rtype::Server::run, &serv);
		std::vector<std::string> servList;

		REQUIRE(rfcClient1.ConnectServer(ip, 50000, login1).empty());
		REQUIRE_NOTHROW(rfcClient1.createGame(gameName));

		REQUIRE_NOTHROW(servList = rfcClient2.ConnectServer(ip, 50000, login2));
		REQUIRE(servList.size() == 1);
		REQUIRE(servList[0] == gameName);
		REQUIRE_NOTHROW(rfcClient2.joinGame(gameName));
		serv.stopServer();
		pthread_cancel(t.native_handle());
		t.join();
	}

	SECTION("SERVER CONNECTION PASSWORD")
	{
		std::string password("MDP");
		std::thread t(&rtype::Server::run, &serv);
		std::vector<std::string> servList;

		REQUIRE(rfcClient1.ConnectServer(ip, 50000, login1).empty());
		REQUIRE_NOTHROW(rfcClient1.createGame(gameName, password));

		REQUIRE_NOTHROW(servList = rfcClient2.ConnectServer(ip, 50000, login2));
		REQUIRE(servList.size() == 1);
		REQUIRE(servList[0] == gameName);
		REQUIRE_NOTHROW(rfcClient2.joinGame(gameName, password));
		serv.stopServer();
		pthread_cancel(t.native_handle());
		t.join();
	}
}
