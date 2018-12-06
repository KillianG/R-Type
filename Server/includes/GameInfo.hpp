/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_GAMEINFO_HPP
#define R_TYPE_GAMEINFO_HPP

#include "socket/include/UdpSocket.hpp"
#include "GameEngine.hpp"

namespace rtype
{
	struct gameInfo
	{
		// std::map needed
		gameInfo();
		explicit gameInfo(std::shared_ptr <network::UdpSocket> &socket);
		gameInfo(std::shared_ptr <network::UdpSocket> &socket, std::string password);


		std::string ip;
		int port;

		int nbPlayer;
		bool isPlaying;

		bool isPwd;
		std::string pwd;

		std::shared_ptr <Game::GameEngine> game;
		std::shared_ptr <network::UdpSocket> gameSocket;
	};
}

#endif //R_TYPE_GAMEINFO_HPP
