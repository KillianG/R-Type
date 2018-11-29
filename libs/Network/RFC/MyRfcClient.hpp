/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_MYRFC_HPP
#define R_TYPE_MYRFC_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <regex>
#include <queue>

#include "LOG/Logger.hpp"
#include "Exception/Exception.hpp"
#include "EventManager/EventManager.hpp"
#include "ECS/utiles.hpp"
#include "utilesBase.hpp"

namespace network
{
	/**
	 * Rfc r-Type encapsulation client side
	 * @tparam S encapsulation for the low level socket (UDP or TCP)
	 */
	template<typename S>
	class MyRfcClient
	{
	public:
		static_assert(std::is_base_of<network::ISocketManager, S>::value, "S must derived from the ISocketManager class");

		/**
		 * init the variables
		 * @param socket typename S socket
		 */
		explicit MyRfcClient(S &socket) : m_socket(socket), m_gameId(-1)
		{
			m_playerMoveString.emplace(playerMove::UP, "UP");
			m_playerMoveString.emplace(playerMove::DOWN, "DOWN");
			m_playerMoveString.emplace(playerMove::RIGHT, "RIGHT");
			m_playerMoveString.emplace(playerMove::LEFT, "LEFT");
		}


		~MyRfcClient() = default;

		bool isServerConnected(int timeout=1)
		{
			auto start_time = std::chrono::high_resolution_clock::now();
			auto timeDrop = std::chrono::seconds(timeout);

			if (m_serverId == -1)
				return false;
			if (!m_socket.requestIsEmpty())
				return true;

			try {
				sendRequest(m_serverId, "PING");
			} catch (std::exception &e){
				Logger::log(Logger::LogType::error, std::string("Connection to server error: ") + e.what());
				return false;
			}
			while (m_socket.requestIsEmpty() && std::chrono::high_resolution_clock::now() - start_time < timeDrop) {
			}
			auto &req = m_socket.getRequests();
			if (!req.empty() && req.front().sender == m_serverId && req.front().data == "PONG\r\n") {
				m_socket.getLastRequest();
				return true;
			}
			return false;
		}

		/**
		 * PING PONG
		 * #TODO pk ca marche pas chez Killian ?
		 */
		bool isGameConnected(int timeout=1)
		{
			auto start_time = std::chrono::high_resolution_clock::now();
			auto timeDrop = std::chrono::seconds(timeout);

			if (m_gameId == -1)
				return false;
			if (!m_socket.requestIsEmpty())
				return true;

			try {
				sendRequest(m_gameId, "PING");
			} catch (std::exception &e) {
				Logger::log(Logger::LogType::error, std::string("Connection to game error: ") + e.what());
				return false;
			}
			while (m_socket.requestIsEmpty() && std::chrono::high_resolution_clock::now() - start_time < timeDrop) {
			}
			auto &req = m_socket.getRequests();
			if (req.front().data == "PONG\r\n" && req.front().sender != m_gameId)
				m_gameId = req.front().sender;
			if (!req.empty() && req.front().sender == m_gameId && req.front().data == "PONG\r\n") {
				m_socket.getLastRequest();
				return true;
			}
			return false;
		}
		/**
		 * First connection to the  RFC rtype server
		 * @param login of the player
		 * @return games list
		 */
		std::vector<std::string> ConnectServer(std::string &ip, int port,std::string &login)
		{
			std::vector<std::string> listGames;
			std::string connect("CONNECT " + login + "\r\n");
			std::istringstream s;
			std::string elem;

			m_serverId = m_socket.Write(ip, port, connect);
			while(m_socket.requestIsEmpty()) ;
			auto response = m_socket.getLastRequest();
			if (response.data[response.data.size() - 2] != '\r')
				throw rtype::Exception("RFC ERROR");

			s.str(response.data);
			getline(s, elem);
			if (elem.compare(0, 9, "LIST GAME"))
				throw rtype::Exception(std::string("RFC ERROR") + elem);

			while (getline(s, elem))
				listGames.push_back(elem);
			if (!listGames.empty())
				listGames.back().pop_back();
			return listGames;
		}

		/**
		 * First connection to the  RFC rtype game
		 * @param login
		 * @return
		 */
		std::vector<EntityInfo> FirstConnectToGame(std::string &ip, int port, std::string &login)
		{
			std::vector<EntityInfo> entitiesInfo;
			std::string connect("CONNECT " + login + "\r\n");
			std::istringstream s;
			std::string elem;

			m_gameId = m_socket.Write(ip, port, connect);
			while (m_socket.requestIsEmpty());
			auto response = m_socket.getLastRequest();
			s.str(response.data);
			getline(s, elem);
			if (elem != "GAME INFO")
				throw rtype::Exception(std::string("RFC ERRRO ") + elem);
			m_entityInit = initGame(s);
			return m_entityInit;
		}

		/**
		 * ask to join an r-Type game
		 * @param name game name
		 * @param password game password if there is one
		 */
		gameInfo joinGame(std::string &name, std::string password=std::string(""))
		{
			return connectToGame("JOIN",  name, password);
		}

		/**
		 * ask to create an r-Type game
		 * @param name game name
		 * @param password game password if there is one
		 */
		gameInfo createGame(std::string &name, std::string password=std::string(""))
		{
			return connectToGame("CREATE",  name, password);
		}

		/**
		 * Function call when the server send a ENTITY INFO request
		 * @param request
		 * @return
		 */
		std::vector<EntityInfo> initGame(std::istringstream &s)
		{
			std::string elem;
			std::string tmp;

			std::smatch matches;
			std::regex regex("type: ([0-9]+) sprite:([a-zA-Z0-9\\./_]+) size: ([0-9]+) ([0-9]+)");
			std::regex regexEnd("type: ([0-9]+) sprite:([a-zA-Z0-9\\./_]+) size: ([0-9]+) ([0-9]+)\r");

			EntityInfo t(0, elem, 0, 0);
			std::vector<EntityInfo> toRet;

			while (getline(s, elem))
			{
				if (elem[elem.size() - 1] == '\r')
					regex = regexEnd;
				if (!std::regex_match(elem, matches, regex))
					throw rtype::Exception(std::string("regex error ") + elem);
				tmp = matches[2];
				toRet.emplace_back(std::stoi(matches[1]), matches[2], std::stoi(matches[3]), std::stoi(matches[4]));
			}
			return toRet;
		}

		/**
		 * Function call when the server send a ENTITY request
		 * @param  s the istringstream base on the request
		 * @return the vector of entity position to display
		 */
		std::vector<EntityPos> updateEntity(std::istringstream &s)
		{
			std::string elem;

			std::smatch matches;
			std::regex regex("id: ([0-9]+) type: ([0-9]+) animTime: ([0-9]+) pos: ([-0-9\\.]+) ([-0-9\\.]+)");
			std::regex regexEnd("id: ([0-9]+) type: ([0-9]+) animTime: ([0-9]+) pos: ([-0-9\\.]+) ([-0-9\\.]+)\r");

			std::vector<EntityPos> toRet;
			while (getline(s, elem))
			{
				if (elem[elem.size() - 1] == '\r')
					regex = regexEnd;
				if (!std::regex_match(elem, matches, regex))
					throw rtype::Exception("RFC Error");
				toRet.emplace_back(matches[1], matches[2], matches[3], matches[4], matches[5]);
			}
			return toRet;
		}

		/**
		 * #TODO check server responses for client requests
		 * Command: INFO UPDATE OVER STATS)
		 * check for server requests, validations or Entities updates
		 */
		void checkGameRequest()
		{
			std::istringstream s;
			std::string request;
			std::string elem;

			std::smatch matches;

			while (!m_socket.requestIsEmpty())
			{
				request = m_socket.getLastRequest().data;

				if (request == "PONG\r\n")
					return;
				else if (request.compare(0, 8, "DEADRAT:") == 0) {
					m_deadRat.emplace_back(stoi(request.substr(9)));
					continue ;
				} else if (request.compare(0, 7, "REMOVE:") == 0) {
					m_remove.emplace_back(stoi(request.substr(8)));
					continue ;
				}
				if (request.compare(0, 5, "GAME ") != 0)
					throw rtype::Exception("RFC not reconized : " + request);
				s.str(request);
				getline(s, elem);
				if (elem.compare(5, 4, "INFO") == 0)
					m_entityInit = initGame(s);
				else if (elem.compare(5, 6, "UPDATE") == 0)
					m_entityPos = updateEntity(s);
				else
					throw rtype::Exception("RFC ERROR");
				/*
				** call Client event
				*/
			}
		}

		/**
		 * Tel the server to move the player in that direction
		 */
		void movePlayer(playerMove movement)
		{
			std::string base(std::string("MOVE ") + m_playerMoveString[movement]);
			sendRequest(m_gameId, base);
		}

		/**
		 * send charge fire before the player shot
		 * @param charge nb of charge
		 */
		void chargeFire(int charge)
		{
			std::string base(std::string("FIRE CHARGING ") + std::to_string(charge));
			sendRequest(m_gameId, base);
		}

		/**
		 * Send the player shot
		 * @param charge nb of charge
		 */
		void fire(int charge)
		{
			std::string base("FIRE SHOT " + std::to_string(charge));
			sendRequest(m_gameId, base);
		}

		/**
		 * simple message to leave a game
		 * It remove the game socket to
		 */
		void leave()
		{
			std::string base("LEAVE");

			sendRequest(m_gameId, base);
//			m_socket.removeSocket(m_gameId);
			m_gameId = -1;
		}

		/**
		 * get EntityPos send by the server
		 * EntityPos give info about the entity to print (x, y) link to id and type of entity
		 * @return  vector of entity position
		 */
		std::vector<EntityPos> getEntitiesPos() const
		{
			return m_entityPos;
		}

		/**
		 * geter for the entitiesInit.
		 * It's the information of all EntityType for the GFX
		 * @return vector of EntityInfo
		 */
		std::vector<EntityInfo> getEntitiesInit() const
		{
			return m_entityInit;
		}

		std::vector<size_t> getDeadRat()
		{
			auto vec = m_deadRat;
			m_deadRat.clear();
			return vec;
		}

		std::vector<size_t> getRemove()
		{
			auto vec = m_remove;
			m_remove.clear();
			return vec;
		}

	private:
		/**
		 * It connect the client to a r-type game.
		 * You cane create or just join a game
		 * If the game has a password you need to give it or it will raise an error
		 *  #TODO check server response in case of error
		 * @param type JOIN or CREATE
		 * @param name game name
		 * @param password if the game hase a password it need to be given
		 */
		gameInfo connectToGame(std::string type, std::string &name, std::string &password)
		{
			std::smatch matches;
			std::regex matchResp("SERVER ((?:[0-9]{1,3}\\.){3}[0-9]{1,3}):([0-9]+)");
			gameInfo ginf;

			if (type != "JOIN" && type != "CREATE")
				throw rtype::Exception("Bad call connectToGame");
			if (!password.empty())
				sendRequest(type + " " + name + " PASSWORD: " + password);
			else
				sendRequest(type + " " + name);

			while(m_socket.requestIsEmpty())
				;
			auto response = m_socket.getLastRequest();
			if (!std::regex_search(response.data, matches, matchResp)) {
				throw rtype::Exception("Client error RFC: " + response.data);
			}
			ginf.ip = matches[1].str();
			ginf.port = std::stoi(matches[2]);
			return ginf;
		}

		/**
		 * It just send a request to the server with \r\n (RFC need)
		 * @param toSend request to send
		 */
		void sendRequest(std::string toSend)
		{
			toSend +=  "\r\n";
			m_socket.Write(m_serverId, toSend);
		}

		/**
		 * Send a request to a given socket from socketClient with \r\n (RFC need)
		 * @param toSend message to send
		 * @param socket SocketClient id
		 */
		void sendRequest(int socketId, std::string toSend)
		{
			toSend +=  "\r\n";
			m_socket.Write(socketId, toSend);
		}

		S &m_socket;
		int m_gameId;
		int m_serverId;

		std::vector<EntityPos> m_entityPos;
		std::vector<EntityInfo> m_entityInit;

		std::vector<size_t> m_deadRat;
		std::vector<size_t> m_remove;

		EventManager m_EvtMgr;
		/**
		 * #TODO check server reponse for client requests
		 */
		std::queue<std::string> m_toValidate;

		std::map<playerMove, std::string> m_playerMoveString;
	};
}


#endif //R_TYPE_MYRFC_HPP
