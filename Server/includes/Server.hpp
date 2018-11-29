//
// Created by nhyarlathotep on 20/11/18.
//

#pragma once

#include <thread>
#include <map>
#include <libs/Network/socket/include/UdpSocket.hpp>
#include <libs/Network/socket/include/TcpManager.hpp>

#include "GameEngine.hpp"
#include "RFC/MyRfcServer.hpp"
#include "GameInfo.hpp"


namespace rtype {
	class Server {
	public:
		Server();
		~Server();

		void run();
		void stopServer();
	private:
		void createGame(network::requestInfo &);
		void joinGame(network::requestInfo &);

		std::map<std::string, std::thread> m_games;
		std::map<std::string, gameInfo> m_gamesInfo;
		std::vector<std::string> m_gameName;

		network::TcpManager m_socket;
		network::MyRfcServer<network::TcpManager> m_rfcManager;

		EventManager _evtMgr;
		bool m_working;
	};
}
