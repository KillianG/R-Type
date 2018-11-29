/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <thread>
#include <Network/socket/include/UdpSocket.hpp>
#include "catch.hpp"
#include "RFC/MyRfcClient.hpp"
#include "RFC/MyRfcServer.hpp"

void whaitClientRequest(network::UdpSocket &server)
{
	while (server.requestIsEmpty())
		;
}

void waitPingFromClient(network::MyRfcServer<network::UdpSocket> &serverRfc)
{
	while (serverRfc.requestIsEmpty())
		;
	serverRfc.getLastRequest();
}


TEST_CASE("Test ClientMyRfc udp template", "[Network]")
{
	std::vector<std::string> gameList = {"GAME 1", "GAME 2"};
	std::string resIp("SERVER 127.0.0.1:5000");
	std::string resList("LIST GAME\nGAME 1\nGAME 2\r\n");
	std::string loc("127.0.0.1");
	std::string game("Game 1");

	network::UdpSocket server(5000);
	network::UdpSocket client(5001);
	network::MyRfcClient<network::UdpSocket> clientRfc(client);
	network::MyRfcServer<network::UdpSocket> serverRfc(server);

	SECTION("Test connection Server") {
		std::string login("Test");

		std::thread t(&network::MyRfcClient<network::UdpSocket>::ConnectServer, &clientRfc, std::ref(loc), 5000, std::ref(login));
		whaitClientRequest(server);
		auto res = serverRfc.getLastRequest();
		REQUIRE(res.data == "CONNECT Test\r\n");
		server.Write(res.sender, resList);
		t.join();

		std::thread t1(&network::MyRfcClient<network::UdpSocket>::createGame, &clientRfc, std::ref(game), std::string(""));
		whaitClientRequest(server);
		res = serverRfc.getLastRequest();
		REQUIRE(res.data == "CREATE Game 1\r\n");
		server.Write(res.sender, resIp);
		t1.join();

		std::thread t2(&network::MyRfcClient<network::UdpSocket>::joinGame, &clientRfc, std::ref(game), std::string(""));
		whaitClientRequest(server);
		res = serverRfc.getLastRequest();
		REQUIRE(res.data == "JOIN Game 1\r\n");
		server.Write(res.sender, resIp);
		t2.join();

		REQUIRE(client.requestIsEmpty());
		int timeout {2};
		std::thread t3(&network::MyRfcClient<network::UdpSocket>::isServerConnected, &clientRfc, timeout);
		whaitClientRequest(server);
		res = serverRfc.getLastRequest();
		REQUIRE(res.data == "PING\r\n");
		REQUIRE(res.sender == 0);
		t3.join();

		std::thread t4(&waitPingFromClient, std::ref(serverRfc));
		REQUIRE(clientRfc.isServerConnected());
		t4.join();
	}

	SECTION("Test Entity geter") {
		std::vector<network::EntityPos> entityPos;
		std::vector<network::EntityInfo> entityInit;
		std::istringstream s;
		std::string init("type: 0 sprite:./sprite/1.jpg size: 0 0\n"
				 "type: 1 sprite:./sprite/2.jpg size: 0 0\n"
				 "type: 2 sprite:./sprite/3.jpg size: 0 0\r\n");

		s.str(init);
		REQUIRE_NOTHROW(entityInit = clientRfc.initGame(s));
		std::string EntityList("id: 1 type: 0 animTime: 1 pos: 1 1\n"
				       "id: 2 type: 1 animTime: 1 pos: 1 2\n"
				       "id: 3 type: 1 animTime: 1 pos: 2 1\n"
				       "id: 4 type: 2 animTime: 1 pos: 2 2\r\n");
		std::istringstream s2;
		s2.str(EntityList);
		REQUIRE_NOTHROW(entityPos = clientRfc.updateEntity(s2));
		REQUIRE(entityPos[0].entityId == 1);
		REQUIRE(entityPos[1].entityId == 2);
		REQUIRE(entityPos[2].entityId == 3);
		REQUIRE(entityPos[3].entityId == 4);

		REQUIRE(entityPos[0].entityType == 0);
		REQUIRE(entityPos[1].entityType == 1);
		REQUIRE(entityPos[2].entityType == 1);
		REQUIRE(entityPos[3].entityType == 2);

		REQUIRE(entityPos[0].Y == 1);
		REQUIRE(entityPos[1].Y == 2);
		REQUIRE(entityPos[2].Y == 1);
		REQUIRE(entityPos[3].Y == 2);

		REQUIRE(entityPos[0].X == 1);
		REQUIRE(entityPos[1].X == 1);
		REQUIRE(entityPos[2].X == 2);
		REQUIRE(entityPos[3].X == 2);
	}
}

TEST_CASE("Test ServerMyRfc Udp template", "[Network]")
{
	std::vector<std::string> gameLists = {"Game1", "Coucou", "cc"};
	network::UdpSocket server(5000);
	network::UdpSocket client(5001);
	network::MyRfcClient<network::UdpSocket> clientRfc(client);
	network::MyRfcServer<network::UdpSocket> serverRfc(server);
	std::string loc("127.0.0.1");
	std::string login("Test");
	network::requestInfo info;

	SECTION("Test ServerRfc connection")
	{
		std::thread t(&network::MyRfcClient<network::UdpSocket>::ConnectServer, &clientRfc, std::ref(loc), 5000, std::ref(login));
		while (serverRfc.requestIsEmpty()) ;
		REQUIRE_NOTHROW(info = serverRfc.getLastRequest());
		REQUIRE_NOTHROW(serverRfc.gameList(gameLists, info.sender));
		t.join();
		std::thread t2(&network::MyRfcClient<network::UdpSocket>::joinGame, &clientRfc, std::ref(gameLists[1]), std::string(""));
		REQUIRE_NOTHROW(serverRfc.reponseGameIp(loc, 5000, info.sender));
		t2.join();
	}
	SECTION("Test serverRfc game send") {
		std::string path1("./sprite1");
		std::string path2("./sprite2");
		std::string path3("./sprite3");

		std::vector<network::EntityInfo> entityInit;
		entityInit.emplace_back(1, path1, 0, 0);
		entityInit.emplace_back(2, path2, 0, 0);
		entityInit.emplace_back(3, path3, 0, 0);
		std::vector<network::EntityPos> entityPos;
		entityPos.emplace_back(1, 1, 1, 1, 1);
		entityPos.emplace_back(2, 2, 2, 2, 2);
		entityPos.emplace_back(3, 3, 3, 3, 3);
		std::thread t(
			&network::MyRfcClient<network::UdpSocket>::FirstConnectToGame,
			&clientRfc, std::ref(loc), 5000, std::ref(login));
		while (serverRfc.requestIsEmpty());
		REQUIRE_NOTHROW(info = serverRfc.getLastRequest());
		REQUIRE_NOTHROW(serverRfc.entitiesInit(entityInit, info.sender));
		t.join();

		REQUIRE_NOTHROW(serverRfc.entitiesPos(entityPos, info.sender));
		while (client.requestIsEmpty());
		REQUIRE_NOTHROW(clientRfc.checkGameRequest());
		auto elem = clientRfc.getEntitiesPos();
		REQUIRE(elem[0].entityId == 1);
		REQUIRE(elem[0].entityType == 1);
		REQUIRE(elem[0].X == 1);
		REQUIRE(elem[0].Y == 1);

		REQUIRE(elem[1].entityId == 2);
		REQUIRE(elem[1].entityType == 2);
		REQUIRE(elem[1].X == 2);
		REQUIRE(elem[1].Y == 2);

		REQUIRE(elem[2].entityId == 3);
		REQUIRE(elem[2].entityType == 3);
		REQUIRE(elem[2].X == 3);
		REQUIRE(elem[2].Y == 3);
		serverRfc.sendDead(1);
		while (client.requestIsEmpty()) ;
		clientRfc.checkGameRequest();
		REQUIRE(clientRfc.getDeadRat().size() == 1);

		serverRfc.sendDead(1);
		while (client.requestIsEmpty()) ;
		clientRfc.checkGameRequest();
		serverRfc.sendDead(2);
		while (client.requestIsEmpty()) ;
		clientRfc.checkGameRequest();
		REQUIRE(clientRfc.getDeadRat().size() == 2);

		serverRfc.sendDead(1);
		while (client.requestIsEmpty()) ;
		clientRfc.checkGameRequest();
		serverRfc.sendDead(2);
		while (client.requestIsEmpty()) ;
		clientRfc.checkGameRequest();
		std::vector<size_t> d;
		d = clientRfc.getDeadRat();
		REQUIRE(d[0] == 1);
		REQUIRE(d[1] == 2);
	}
}
