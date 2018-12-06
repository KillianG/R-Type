/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
** Made on 2018/11 by ebernard
*/

#include "Logger.hpp"
#include "includes/Server.hpp"

int main(int argc, char **argv)
{
	try {
		rtype::Server server;

		server.run();
	} catch (std::exception &e) {
		Logger::log(Logger::LogType::error, e.what());
		return 84;
	}
	return 0;
}
