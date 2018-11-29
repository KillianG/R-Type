/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <boost/bind.hpp>
#include <boost/array.hpp>

#include "LOG/Logger.hpp"
#include "socket/include/UdpSocket.hpp"

/**
 * UdpSocket boost encapsualtion Constructor
 * It create a thread for boost io service listener
 * and start listening for request
 * @param port number for thesocket
 */
network::UdpSocket::UdpSocket(int port) :
	m_serviceThread(nullptr),
	m_socket(nullptr),
	m_localIp(firstGetIp()),
	m_localPort(port)
{
	m_socket = std::make_shared<boost::asio::ip::udp::socket>(m_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port));
	this->AsyncRead();
}

/**
 * Destructor
 * it terminate the io service thread and close the socket
 * No free needed because we work with smart pointeur
 */
network::UdpSocket::~UdpSocket()
{
	if (m_serviceThread != nullptr) {
		m_service.stop();
		m_serviceThread->join();
	}
	if (m_socket != nullptr)
		m_socket->close();
}

/**
 * It juste save a ip and port to the connected client vector
 * @param ip client address ip
 * @param port client port
 * @return the index of the client
 */
size_t network::UdpSocket::Connect(std::string &ip, std::size_t port)
{
	int index;
	auto findEndPoint = std::find_if(m_connected.begin(), m_connected.end(),
					 [ip, port](boost::asio::ip::udp::endpoint &cmp) {
						 return cmp.address() == boost::asio::ip::address::from_string(ip) && cmp.port() == port;
					 });

	if (findEndPoint == m_connected.end()) {
		m_connected.emplace_back(boost::asio::ip::address::from_string(ip), port);
		index = m_connected.size() - 1;
	} else
		index = m_connected.end() - findEndPoint;

	return index;
}

/**
 * Read the socket asyncronously
 */
void network::UdpSocket::AsyncRead()
{
	m_socket->async_receive_from(boost::asio::buffer(m_buffer),
				     m_endpoint,
				     boost::bind(&network::UdpSocket::handle_receive, this,
						 boost::asio::placeholders::error,
						 boost::asio::placeholders::bytes_transferred)
	);
	if(!m_serviceThread)
		m_serviceThread = std::make_shared<std::thread>(boost::bind(&boost::asio::io_service::run, &m_service));
}


/**
 * Function call when a request is get
 * It push back the request to the queue
 * @param error boost error if there is one
 * @param size size readed
 */
void network::UdpSocket::handle_receive(const boost::system::error_code &error, std::size_t size)
{
	int index;
	std::string tmp;
	std::string buf;

	if (!error || error == boost::asio::error::message_size) {
		auto findEndPoint = std::find_if(m_connected.begin(), m_connected.end(),
						 [this](const boost::asio::ip::udp::endpoint cmp) {
							 return cmp.address() == m_endpoint.address() && cmp.port() == m_endpoint.port();
						 });
		if (findEndPoint == m_connected.end()) {
			m_connected.push_back(m_endpoint);
			index = m_connected.size() - 1;
		} else
			index = findEndPoint  - m_connected.begin() ;
		m_buffer[size] = 0;
		m_request.push(requestInfo{index, std::string(m_buffer.data())});
		m_socket->async_receive_from(boost::asio::buffer(m_buffer),
					     m_endpoint,
					     boost::bind(&network::UdpSocket::handle_receive, this,
							 boost::asio::placeholders::error,
							 boost::asio::placeholders::bytes_transferred)
		);
	} else {
		Logger::log(Logger::LogType::error,
			    std::string("AsyncRead boost error: ") +
			    error.message());
	}
}

/**
 * Send to a given ip and addres
 * If the Ip and address is not in the client vector it will be added
 * @param ip client ip
 * @param port client socket port
 * @param toSend the data to send
 * @return the created socket id
 */
int network::UdpSocket::Write(std::string &ip, int port, std::string &toSend)
{
	int index;

	auto findEndPoint = std::find_if(m_connected.begin(), m_connected.end(),
					 [ip, port](boost::asio::ip::udp::endpoint &cmp) {
						 return cmp.address().to_string() == ip && cmp.port() == port;
					 });
	if (findEndPoint == m_connected.end()) {
		m_connected.emplace_back(boost::asio::ip::address::from_string(ip), port);
		index = m_connected.size() - 1;
	} else
		index = findEndPoint - m_connected.begin();

	m_socket->send_to(boost::asio::buffer(toSend), m_connected[index]);
	return index;
}

/**
 * send to a client id the data
 * @param id clientId in the vector
 * @param toSend data sended to the client
 * @return the socket id
 */
int network::UdpSocket::Write(int id, std::string &toSend)
{
	m_socket->send_to(boost::asio::buffer(toSend), m_connected[id]);
	return id;
}

/**
 * Check if the request queue is empty
 * @return is empty or not
 */
bool network::UdpSocket::requestIsEmpty() const
{
	return m_request.empty();
}

/**
 * Get the last request
 * @return requestInfo whit the data and the clientId
 */
network::requestInfo network::UdpSocket::getLastRequest()
{
	network::requestInfo back = m_request.front();
	m_request.pop();
	return back;
}

/**
 * a function that get the local ip
 * @return the localIp of the computer
 */
std::string network::UdpSocket::firstGetIp()
{
	boost::asio::ip::address  addr;
	try {
		boost::asio::io_service netService;
		boost::asio::ip::udp::resolver   resolver(netService);
		boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "google.com", "");
		boost::asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);
		boost::asio::ip::udp::endpoint ep = *endpoints;
		boost::asio::ip::udp::socket socket(netService);
		socket.connect(ep);
		addr = socket.local_endpoint().address();
	} catch (std::exception& e){
		Logger::log(Logger::LogType::error, std::string("firstGetIp ") + e.what());
		return "127.0.0.1";
	}
	return addr.to_string();
}

/**
 * @return  the saved localIp
 */
std::string network::UdpSocket::getIp()
{
	return m_localIp;
}

/**
 * @return the socket port
 */
int network::UdpSocket::getPort()
{
	return m_localPort;
}

/**
 * All requests get by the socket
 * @return the request queue
 */
const std::queue<network::requestInfo> &network::UdpSocket::getRequests() const
{
	return m_request;
}

void network::UdpSocket::removeClosedSocket()
{

}

/**
 * @return  the saved localIp
 */
std::string network::UdpSocket::getIp(int socketId)
{
	return m_connected[socketId].address().to_string();
}
