/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_MYRFCSERVER_HPP
#define R_TYPE_MYRFCSERVER_HPP

#include <map>
#include <vector>

#include "../../../Server/includes/Utils.hpp"
#include "Exception/Exception.hpp"
#include "MyRfcClient.hpp"

namespace network
{
	/**
	 * Rfc r-Type encapsulation server side
	 * @tparam S encapsulation for the low level socket (UDP or TCP)
	 */
	template<typename S>
	class MyRfcServer {
	public:
		static_assert(std::is_base_of<network::ISocketManager, S>::value, "S must derived from the ISocketManager class");

		explicit MyRfcServer(S &socket) :
			m_socket(socket)
		{
			m_movePlayer.emplace(std::string("UP"), Game::MovementDir::up);
			m_movePlayer.emplace(std::string("DOWN"), Game::MovementDir::down);
			m_movePlayer.emplace(std::string("RIGHT"), Game::MovementDir::right);
			m_movePlayer.emplace(std::string("LEFT"), Game::MovementDir::left);
		}

		~MyRfcServer() = default;

		/**
		 * Get last request from every client
		 * @return  requestInfo for the last request (the message and the client socket id)
		 */
		requestInfo getLastRequest()
		{
			requestInfo req = m_socket.getLastRequest();
			std::string pong("PONG");
			std::regex loginRegex("CONNECT ([a-zA-Z0-9]+)\r\n");

			if (req.sender == -1) {
				std::cout << "player disconnect" << std::endl;

				m_socket.removeClosedSocket();
				return req;
			}
			if (req.data == "PING\r\n") {
				Logger::log(Logger::LogType::info, std::to_string(req.sender) + " " + req.data + "ping");
				sendRequest(pong, req.sender);
			}
			else if (m_client.find(req.sender) == m_client.end()) {
				std::smatch loginSmatch;

				if (!std::regex_search(req.data, loginSmatch, loginRegex))
					throw rtype::Exception("regex connection error");
				m_client.emplace(req.sender, loginSmatch[1]);
			}
			return  req;
		}

		/**
		 * Check if there is any request in the queue
		 * @return empty()
		 */
		bool requestIsEmpty()
		{
			return m_socket.requestIsEmpty();
		}

		/**
		 * EntityPos serializer for RFC
		 * @param entities list of entityPos to serialize
		 */
		void entitiesPos(const std::vector<EntityPos> &entities)
		{
			std::string req("GAME UPDATE\n");

			for (auto &&pos : entities) {
				req += pos.to_str() + '\n';
			}
			req.pop_back();
			for (auto &&elem : m_client)
				sendRequest(req, elem.first);
		}

		/**
		 * EntityPos serializer for RFC
		 * @param entities list of entityPos to serialize
		 * @param socket the client to send the info
		 */
		void entitiesPos(std::vector<EntityPos> &entities, int socket)
		{
			std::string req("GAME UPDATE\n");

			if (entities.empty())
				throw rtype::Exception("Entities list is emtpy");
			for (auto &&pos : entities) {
				req += pos.to_str() + '\n';
			}
			req.pop_back();
			sendRequest(req, socket);
		}

		/**
		 * EntityInfo serializer for RFC
		 * @param entities list of entityPos to serialize
		 */
		void entitiesInit(std::vector<EntityInfo> &entities)
		{
			std::string req("GAME INFO\n");

			if (entities.empty())
				throw rtype::Exception("Entities list is emtpy");
			for (auto &&pos : entities) {
				req += pos.to_str() + '\n';
			}
			req.pop_back();
			for (auto &&elem : m_client)
				sendRequest(req, elem.first);
		}

		/**
		 * EntityInfo serializer for RFC
		 * @param entities list of EntityInfo to send
		 * @param socket the client id to send the info
		 */
		void entitiesInit(std::vector<EntityInfo> &entities, int socket)
		{
			std::string req("GAME INFO\n");

			if (entities.empty())
				throw rtype::Exception("Entities list is emtpy");
			for (auto &&pos : entities) {
				req += pos.to_str() + '\n';
			}
			req.pop_back();
			sendRequest(req, socket);
		}

		/**
		 * game name vector serializer for RFC
		 * it send the all games name the te client
		 * @param entities list of the games name to send
		 * @param socket the socket client id to send the info
		 */
		void gameList(std::vector<std::string> &names, int socket)
		{
			std::string req("LIST GAME\n");

			for (auto &&game : names) {
				req += game + "\n";
			}
			req.pop_back();
			sendRequest(req, socket);
		}

		/**
		 * Send to the given client witch port and ip he must connect to play
		 * @param ip game ip
		 * @param port  game port
		 * @param socket Client id to send the info
		 */
		void reponseGameIp(std::string &ip, int port, int socket)
		{
			std::string req("SERVER ");

			req += ip + ":" + std::to_string(port);
			sendRequest(req, socket);
		}

		Game::MovementDir getPlayerMove(std::string &&move)
		{
			if (m_movePlayer.find(move) != m_movePlayer.end())
				return  m_movePlayer[move];
			return Game::MovementDir::none;
		}

		void sendRemove(size_t id)
		{
			std::string d("REMOVE: ");
			std::string req(d + std::to_string(id));

			for (auto &&elem : m_client) {
				sendRequest(req, elem.first);
			}
		}

		void sendDead(size_t id)
		{
			std::string d("DEADRAT: ");
			std::string req(d + std::to_string(id));

			for (auto &&elem : m_client) {
				sendRequest(req, elem.first);
			}
		}

		/**
		 * Send a request to a given socket from socketClient with \r\n (RFC need)
		 * @param toSend message to send
		 * @param socket Client id to send the info
		 */
		void sendRequest(std::string toSend, int socket)
		{
			toSend +=  "\r\n";
			m_socket.Write(socket, toSend);
		}
	private:

		S &m_socket;
		std::map<int, std::string> m_client;
		std::map<std::string, Game::MovementDir > m_movePlayer;
	};
}


#endif //R_TYPE_MYRFCSERVER_HPP
