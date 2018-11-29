/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_UDPSOCKET_HPP
#define R_TYPE_UDPSOCKET_HPP

#include <string>
#include <queue>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "ISocketManager.hpp"

namespace network
{
	class UdpSocket : public ISocketManager
	{
	public:
		UdpSocket(int port);
		~UdpSocket();

		int Write(int id, std::string &) override;
		int Write(std::string &ip, int port, std::string &toSend);

		bool requestIsEmpty() const override;
		requestInfo getLastRequest() override;

		std::string getIp() override;
		int getPort() override;

		std::string getIp(int socketId);

		size_t Connect(std::string &ip, std::size_t port);
		const std::queue<requestInfo> &getRequests() const override;

		void removeClosedSocket() override;
	private:
		void AsyncRead();
		std::string firstGetIp();
		void handle_receive(const boost::system::error_code &error, std::size_t);

		boost::asio::io_service m_service;
		std::shared_ptr<std::thread> m_serviceThread;


		boost::asio::ip::udp::endpoint m_endpoint;
		std::shared_ptr<boost::asio::ip::udp::socket> m_socket;

		std::vector<boost::asio::ip::udp::endpoint> m_connected;
		std::queue<requestInfo> m_request;

		std::string m_localIp;
		int m_localPort;
		boost::array<char, 4096> m_buffer;
	};
}


#endif //R_TYPE_UDPSOCKET_HPP
