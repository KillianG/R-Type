/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <Network/socket/include/TcpSocket.hpp>


#include "LOG/Logger.hpp"
#include "socket/include/TcpSocket.hpp"
#include "socket/include/TcpManager.hpp"

/**
 * Constructor for basic assync socket
 * @param io_service service listen by all socket
 * @param request request queue use by the manager
 * @param id sockeId given by the manager
 */
network::TcpSocket::TcpSocket(boost::asio::io_service& io_service, std::queue<requestInfo> &request, int id) :
	m_socket(io_service),
	m_request(request),
	m_socketId(id)
{
}

/**
 * @return a ref to the boost socket
 */
boost::asio::ip::tcp::socket &network::TcpSocket::getSocket()
{
	return m_socket;
}

/**
 * start listen to the socket
 */
void network::TcpSocket::start()
{
	boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer),
				boost::asio::transfer_at_least(1),
				boost::bind(&TcpSocket::handleReadContent, this,
					    boost::asio::placeholders::error,
					    boost::asio::placeholders::bytes_transferred
					    ));
}


/**
 * Handler call when the socket read somthing
 * It push a request to the queue if there is no error
 * @param err boost error if ther is one
 * @param bytes_transferred number of byte read
 */
void network::TcpSocket::handleReadContent(const boost::system::error_code& err, std::size_t bytes_transferred)
{
	network::requestInfo req;

	if (err == boost::asio::error::eof) {
		this->close();
		req.data = std::string("");
		req.sender = m_socketId;
		m_request.push(req);
		Logger::log(Logger::LogType::info, std::string("TCP EOF"));
		return ;
	}
	if (!err)
	{
		m_buffer[bytes_transferred] = 0;
		Logger::log(Logger::LogType::info, std::string("tcp read") + m_buffer.data());
		req.data = std::string(m_buffer.data());
		req.sender = m_socketId;
		m_request.push(req);
		boost::asio::async_read(m_socket, boost::asio::buffer(m_buffer),
					boost::asio::transfer_at_least(1),
					boost::bind(&TcpSocket::handleReadContent, this,
						    boost::asio::placeholders::error,
						    boost::asio::placeholders::bytes_transferred));
	} else {
		Logger::log(Logger::LogType::error, "read error " + err.message());
	}
}

/**
 * Send a request to the linked Tcp Socket
 * @param toSend message send
 */
void network::TcpSocket::sendRequest(std::string &toSend)
{
	m_socket.send(boost::asio::buffer(toSend));
}

/**
 * Connect to a given server
 * @param ip server
 * @param port server
 */
void network::TcpSocket::connect(std::string &ip, int port)
{
	boost::asio::ip::address addr = boost::asio::ip::address::from_string(ip);

	m_socket.connect(boost::asio::ip::tcp::endpoint(addr, port));
}

/**
 * Get the socket port
 * @return the socket port
 */
int network::TcpSocket::getPort() const
{
	return m_socket.remote_endpoint().port();
}

/**
 * Get the local ip of the computer
 * @return local ip of the computer
 */
std::string network::TcpSocket::getIp() const
{
	return m_socket.remote_endpoint().address().to_string();
}

/**
 * Close the socket and set the socketId to -1
 * So the manager can remove it from the socket list
 */
void network::TcpSocket::close()
{
	m_socketId = -1;
	if (m_socket.is_open())
		m_socket.close();
}
