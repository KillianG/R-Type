/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "catch.hpp"
#include "socket/include/TcpManager.hpp"

TEST_CASE("Boost Tcp test", "[Network]")
{
	std::string localHost = std::string("127.0.0.1");
	std::string test("TEST STRING");
	SECTION("Test TcpSocket") {
		network::TcpManager socketManager1(5007);
		network::TcpManager socketManager2(5008);

		REQUIRE(socketManager1.getPort() == 5007);
		REQUIRE(socketManager2.getPort() == 5008);

		REQUIRE(socketManager2.requestIsEmpty());
		REQUIRE(socketManager1.requestIsEmpty());

		REQUIRE_NOTHROW(socketManager2.startAccept());
		REQUIRE_NOTHROW(socketManager1.Write(localHost, 5008, localHost));

		while(socketManager2.requestIsEmpty()) ;
		REQUIRE_FALSE(socketManager2.requestIsEmpty());
		auto elem = socketManager2.getLastRequest();
		REQUIRE(elem.data == localHost);
		REQUIRE(elem.sender == 0);

		REQUIRE_NOTHROW(socketManager1.Write(0, test));

		while(socketManager2.requestIsEmpty()) ;
		REQUIRE_FALSE(socketManager2.requestIsEmpty());
		elem = socketManager2.getLastRequest();
		REQUIRE(elem.sender == 0);
		REQUIRE(elem.data == test);
		REQUIRE_NOTHROW(socketManager2.Write(elem.sender, localHost));

		while(socketManager1.requestIsEmpty()) ;

		elem = socketManager1.getLastRequest();
		REQUIRE(elem.sender == 0);
		REQUIRE(elem.data == localHost);

		REQUIRE_NOTHROW(socketManager1.Write(0, localHost));
		REQUIRE_NOTHROW(socketManager1.Write(0, test));
		REQUIRE_NOTHROW(socketManager1.Write(0, localHost));
		REQUIRE_NOTHROW(socketManager1.Write(0, test));

		while(socketManager2.requestIsEmpty()) ;
		REQUIRE_FALSE(socketManager2.requestIsEmpty());
	}
}
