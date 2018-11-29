/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_TCPMANAGER_HPP
#define R_TYPE_TCPMANAGER_HPP

#include <boost/asio.hpp>
#include "TcpSocket.hpp"
#include "ISocketManager.hpp"

namespace network
{
	class TcpManager : public ISocketManager
	{
	public:
		TcpManager(int port);
		~TcpManager();

		size_t Connect(std::string &ip, int port);

		int Write(int id, std::string &) override;
		int Write(std::string &ip, int port, std::string &toSend) override;

		bool requestIsEmpty() const override;
		requestInfo getLastRequest() override;

		std::string getIp() override;
		int getPort() override;
		void startAccept();
		const std::queue<requestInfo> &getRequests() const override;

		void removeClosedSocket() override;
	private:
		void handleAccept(std::shared_ptr<TcpSocket> new_connection, const boost::system::error_code &error);

		std::string firstGetIp();

		boost::asio::io_service m_io;
		std::shared_ptr<std::thread> m_ioRunThread;
		boost::asio::ip::tcp::endpoint m_endPoint;
		boost::asio::ip::tcp::acceptor m_acceptor;

		std::vector<std::shared_ptr<TcpSocket>> m_client;
		std::queue<requestInfo> m_request;
		int m_listenPort;
		std::string m_localIp;
	};
}

#else

namespace network {
	class TcpManager;
};

#endif // R_TYPE_TCPMANAGER_HPP
