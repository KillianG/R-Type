/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <boost/bind.hpp>
#include <boost/exception/all.hpp>


#include "LOG/Logger.hpp"
#include "socket/include/TcpManager.hpp"
#include "socket/include/TcpSocket.hpp"

/**
 * Construcotr that creat an acceptor for the given port
 * It get the compteur local ip
 * @param port port for the acceptor
 */
network::TcpManager::TcpManager(int port) :
	m_endPoint(boost::asio::ip::tcp::v4(), port),
	m_acceptor(m_io, m_endPoint),
	m_listenPort(port),
	m_localIp(firstGetIp())
{
}

/**
 * Stop the io stream and join the thread
 */
network::TcpManager::~TcpManager()
{
	Logger::log(Logger::LogType::info, "destructor tcp");
	m_io.stop();
	if (m_ioRunThread)
		m_ioRunThread->join();
}


/**
 * a function that get the local ip
 * @return the localIp of the computer
 */
std::string network::TcpManager::firstGetIp()
{
	boost::asio::ip::address  addr;
	try {
		boost::asio::io_service netService;
		boost::asio::ip::udp::resolver   resolver(netService);
		boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), boost::asio::ip::host_name(), "");
		boost::asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);
		boost::asio::ip::udp::endpoint ep = *endpoints;

		addr = ep.address();
		std::cout << ep.address().to_string() << std::endl;
	} catch (std::exception& e) {
		Logger::log(Logger::LogType::error, std::string("connection to google.fr failed: ") + e.what());
		return "127.0.0.1";
	}
	return addr.to_string();
}

/**
 * Connect a new socket to the given port and ip
 * @param ip Server ip
 * @param port Server port
 * @return The index of the created socket
 */
size_t network::TcpManager::Connect(std::string &ip, int port)
{
	auto find = find_if(m_client.begin(), m_client.end(),
		[ip, port](const TcpSocket::ptr sock) {
		return sock->getIp() == ip && sock->getPort() == port;
	});

	if (find != m_client.end())
		return find - m_client.begin();
	auto elem = std::make_shared<TcpSocket>(m_io, m_request, m_client.size());
	elem->connect(ip, port);
	elem->start();

	if (!m_ioRunThread)
		m_ioRunThread = std::make_shared<std::thread>(boost::bind(&boost::asio::io_service::run, &m_io));
	Logger::log(Logger::LogType::info, "connected to: " + ip + " port: " + std::to_string(port));
	m_client.push_back(elem);
	return m_client.size() - 1;
}

/**
 * send the string to the client on the id
 * @param id socket id to send
 * @param toSend the string to send
 * @return the id of the socket
 */
int network::TcpManager::Write(int id, std::string &toSend)
{
	m_client[id]->sendRequest(toSend);
	if (!m_ioRunThread)
		m_ioRunThread = std::make_shared<std::thread>(boost::bind(&boost::asio::io_service::run, &m_io));
	return id;
}

/**
 * Send the string to the socket with this port and ip
 * If the socket doesn't exist, the manager create and connect a to the given port and ip
 * @param ip Server ip
 * @param port  Server port
 * @param toSend String to send
 * @return the id of the created or existing socket
 */
int network::TcpManager::Write(std::string &ip, int port, std::string &toSend)
{
	TcpSocket::ptr res;
	int id;

	auto find = std::find_if(m_client.begin(), m_client.end(), [ip, port](const std::shared_ptr<network::TcpSocket> &cmp){
		return cmp->getIp() == ip && cmp->getPort() == port;
		     }
	);

	if (find == m_client.end()) {
		id = Connect(ip, port);
		res = m_client[id];
		res->start();
	} else {
		id = find - m_client.begin();
		res = *find;
	}

	res->sendRequest(toSend);
	if (!m_ioRunThread)
		m_ioRunThread = std::make_shared<std::thread>(boost::bind(&boost::asio::io_service::run, &m_io));
	return id;
}

/**
 * Check if there is any request pending
 * @return is ther any request
 */
bool network::TcpManager::requestIsEmpty() const
{
	return m_request.empty();
}

/**
 * Return the last pending request
 * @return  the last request
 */
network::requestInfo network::TcpManager::getLastRequest()
{
	auto back =  m_request.front();
	m_request.pop();
	return back;
}

/**
 * @return get the local ip of this computer
 */
std::string network::TcpManager::getIp()
{
	return m_localIp;
}

/**
 *
 * @return get the listening port
 */
int network::TcpManager::getPort()
{
	return m_listenPort;
}

/**
 * Start accept new connection on the port given to the constructor
 */
void network::TcpManager::startAccept()
{
	try {
		Logger::log(Logger::LogType::info, "Start accept connection");
		m_client.push_back(std::make_shared<TcpSocket>(m_acceptor.get_io_service(), m_request, m_client.size()));
		m_acceptor.async_accept(m_client.back()->getSocket(),
					boost::bind(&TcpManager::handleAccept, this,
						m_client.back(), boost::asio::placeholders::error));
	} catch (boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::system::system_error>> &e) {
		std::cout <<  boost::diagnostic_information(e) << std::endl;
	}
	if (!m_ioRunThread)
		m_ioRunThread = std::make_shared<std::thread>(boost::bind(&boost::asio::io_service::run, &m_io));
}

/**
 * Start socket read and wait for a new connection
 * @param new_connection TcpSocket pointer just accepted
 * @param error boost acceptor error
 */
void network::TcpManager::handleAccept(std::shared_ptr<TcpSocket> new_connection,
					  const boost::system::error_code &error)
{
	if (!error) {
		Logger::log(Logger::LogType::info, "Accept new client ip: " + new_connection->getIp() +
						   " port " + std::to_string(new_connection->getPort()));
		new_connection->start();
		startAccept();
	}
	else
		Logger::log(Logger::LogType::error, std::string("accept error: ") + error.category().name());
}

/**
 * All requests get by the socket
 * @return the request queue
 */
const std::queue<network::requestInfo> &network::TcpManager::getRequests() const
{
	return m_request;
}

/**
 * Remove closed socket
 */
void network::TcpManager::removeClosedSocket()
{
	for (auto it = m_client.begin(); it != m_client.end(); )
	{
		if ((*it)->getSocket().is_open())
			it = m_client.erase(it);
		else
			++it;
	}
}
