/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_ISOCKETMANAGER_HPP
#define R_TYPE_ISOCKETMANAGER_HPP

#include <queue>
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>

#include "Exception/Exception.hpp"
#include "networkUtils.hpp"

namespace network
{
	/**
	 * Interface for the socket encapsulation
	 * So Udp or Tcp can be used
	 */
	class ISocketManager
	{
	public:
		virtual ~ISocketManager() = default;
		virtual int Write(int id, std::string &) = 0;
		virtual int Write(std::string &, int port, std::string &) = 0;

		virtual bool requestIsEmpty() const = 0;
		virtual requestInfo getLastRequest() = 0;

		virtual std::string getIp() = 0;
		virtual int getPort() = 0;
		virtual const std::queue<network::requestInfo> &getRequests() const = 0;
		virtual void removeClosedSocket() = 0;
	};
}


#endif //R_TYPE_ISOCKETMANAGER_HPP
