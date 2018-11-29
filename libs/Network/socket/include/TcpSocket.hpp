/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_TCPSOCKET_HPP
#define R_TYPE_TCPSOCKET_HPP

#include <memory>
#include <queue>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "networkUtils.hpp"

namespace network
{
	class TcpSocket
	{
	public:
		typedef std::shared_ptr<network::TcpSocket> ptr;

		TcpSocket(boost::asio::io_service& io_service, std::queue<requestInfo> &request, int id);
		~TcpSocket() = default;

		void start();
		void handleReadContent(const boost::system::error_code &, std::size_t);
		void sendRequest(std::string &);

		void connect(std::string&ip, int port);
		boost::asio::ip::tcp::socket &getSocket();

		std::string getIp() const;
		int getPort() const;

		void close();
	private:
		boost::asio::ip::tcp::socket m_socket;
		std::queue<requestInfo> &m_request;
		boost::array<char, 4096> m_buffer;

		int m_socketId;
	};
}


#else

namespace network {
	class TcpSocket;
};


#endif //R_TYPE_TCPSOCKET_HPP
