//
// Created by nhyarlathotep on 20/11/18.
//

#include "Network/socket/include/UdpSocket.hpp"
#include "Server.hpp"
#include "LOG/Logger.hpp"

/**
 * init all attributes
 */
rtype::Server::Server() :
        m_socket(50000),
        m_rfcManager(m_socket),
        m_working(true)
{
	Logger::log(Logger::LogType::info, std::string("server port: ") + std::to_string(m_socket.getPort()));
	Logger::log(Logger::LogType::info, std::string("ip local ") + m_socket.getIp());
}

/**
 * Destroy all running thread and game
 */
rtype::Server::~Server()
{
    for (auto &elem : m_gamesInfo){
        elem.second.isPlaying = false;
    }

    for (auto &elem : m_games) {
    	m_gamesInfo[elem.first].game->stopGame();
        pthread_cancel(elem.second.native_handle());
        elem.second.join();
    }
}


/**
 * search the game and send the ip and port of the given game
 * @param request rfc request that asked it
 */
void rtype::Server::joinGame(network::requestInfo &request)
{
    std::regex format("JOIN ([a-zA-Z0-9 ]+) PASSWORD: ([a-zA-Z0-9 ]+)");
    std::regex formatNoPsd("JOIN ([a-zA-Z0-9 ]+)");
    std::smatch matches;
    bool pswd;

    request.data.pop_back();
    request.data.pop_back();
    pswd = std::regex_match(request.data, matches, format);

    if (!pswd && !std::regex_match(request.data, matches, formatNoPsd))
        throw rtype::RfcException("RFC format error " + request.data);

    auto elem = std::find(m_gameName.begin(), m_gameName.end(), matches[1].str());

    if (elem == m_gameName.end())
        throw rtype::RfcException("Game not found");

    if (m_gamesInfo[matches[1].str()].nbPlayer == 4)
        throw rtype::RfcException("Game is Full");

    if (!pswd && m_gamesInfo[matches[1].str()].isPwd)
        throw rtype::RfcException("Game need password");

    if (pswd && m_gamesInfo[matches[1].str()].isPwd && m_gamesInfo[matches[1].str()].pwd != matches[2].str())
        throw rtype::RfcException("Wrong password");

    m_gamesInfo[matches[1].str()].nbPlayer++;
    m_rfcManager.reponseGameIp(m_gamesInfo[matches[1].str()].ip, m_gamesInfo[matches[1].str()].port, request.sender);
}

/**
 * Create a game and run the gameEngine in a thread
 * send the ip and port of the given game
 * @param request rfc request that asked it
 */
void rtype::Server::createGame(network::requestInfo &request)
{
    std::shared_ptr<network::UdpSocket> socket;
    std::regex format("CREATE ([a-zA-Z0-9 ]+) PASSWORD: ([a-zA-Z0-9 ]+)");
    std::regex formatNoPsd("CREATE ([a-zA-Z0-9 ]+)");
    std::smatch matches;
    bool pswd;

    request.data.pop_back();
    request.data.pop_back();
    pswd = std::regex_match(request.data, matches, format);

    if (!pswd && !std::regex_match(request.data, matches, formatNoPsd))
        throw rtype::RfcException("RFC format error: " + request.data);

    auto elem = std::find(m_gameName.begin(), m_gameName.end(), matches[1].str());

    if (elem != m_gameName.end())
        throw rtype::RfcException("Game already exist");

    socket = std::make_shared<network::UdpSocket>(m_socket.getPort() + m_gamesInfo.size());
    if (!pswd)
        m_gamesInfo.emplace(matches[1].str(), gameInfo(socket));
    if (pswd)
        m_gamesInfo.emplace(matches[1].str(), gameInfo(socket, matches[2].str()));
    m_games.emplace(matches[1].str(), std::thread(&Game::GameEngine::run, m_gamesInfo[matches[1].str()].game.get()));
    m_gameName.push_back(matches[1].str());

    m_rfcManager.reponseGameIp(m_gamesInfo[matches[1].str()].ip, m_gamesInfo[matches[1].str()].port, request.sender);
}

/**
 * infinity loop that accept new client
 * Client can creat or join game
 */
void rtype::Server::run()
{
    network::requestInfo request;

    m_socket.startAccept();
    while (m_working) {
        if (m_socket.requestIsEmpty())
            continue;

        request = m_rfcManager.getLastRequest();
        if (request.data.empty())
            continue;
        try {
            if (!request.data.compare(0, 8, "CONNECT ")) {
                m_rfcManager.gameList(m_gameName, request.sender);
            } else if (!request.data.compare(0, 5, "JOIN "))
                joinGame(request);
            else if (!request.data.compare(0, 7, "CREATE "))
                createGame(request);
            else {
                throw RfcException(request.data + ": RFC not recognise");
            }
        } catch (rtype::RfcException &e) {
        	m_rfcManager.sendRequest(std::string("ERROR: ") + e.what(), request.sender);
        }
    }
}

/**
 * Stop the server loop
 */
void rtype::Server::stopServer()
{
    for (auto &elem : m_games)
            m_gamesInfo[elem.first].game->stopGame();
    m_working = false;
}

