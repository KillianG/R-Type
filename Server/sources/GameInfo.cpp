/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "GameInfo.hpp"

/**
 * Default constructor
 */
rtype::gameInfo::gameInfo() : port(0), nbPlayer(0), isPlaying(false)
{
}

/**
 * constructor when no password is needed
 * @param socket smart pointer to socket given to the game
 */
rtype::gameInfo::gameInfo(std::shared_ptr <network::UdpSocket> &socket) :
	ip(socket->getIp()), port(socket->getPort()),
	nbPlayer(0), isPlaying(true), isPwd(false),
	gameSocket(socket)
{
	game = std::make_shared<Game::GameEngine>(socket);
}

/**
 * constructor when password is needed
 * @param socket smart pointer to socket given to the game
 * @param password password need by to the game to login
 */
rtype::gameInfo::gameInfo(std::shared_ptr <network::UdpSocket> &socket, std::string password) :
	ip(socket->getIp()), port(socket->getPort()),
	nbPlayer(0), isPlaying(true), isPwd(true),
	pwd(password), gameSocket(socket)
{
	game = std::make_shared<Game::GameEngine>(socket);
}
