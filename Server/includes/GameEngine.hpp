//
// Created by nhyarlathotep on 20/11/18.
//

#pragma once

#include <string>
#include "../../libs/LOG/Logger.hpp"
#include "../../libs/ECS/Manager.hpp"
#include "../../libs/Network/socket/include/UdpSocket.hpp"
#include "../../libs/Network/RFC/MyRfcServer.hpp"
#include "../../libs/EventManager/EventManager.hpp"

#include "Utils.hpp"
#include "GameEvents.hpp"
#include "GameComponents.hpp"

namespace Game {
        struct UserInfo {
        	ecs::Entity _id;
        	std::string _ip;
        };
    /**
     * The game take place here
     */
    class GameEngine : public Receiver<GameEngine> {
    public:
        using clock = std::chrono::steady_clock;

        explicit GameEngine(std::shared_ptr<network::UdpSocket> &udpSocket);

        /*
         * Engine Functions
         */
        void run();
        ecs::Entity addPlayer();
        void stopGame() noexcept;

        void manageRequest();

        void receive(const DrawEvent &event);
        void receive(const RemoveEvent &event);

    private:
        EventManager _evtMgr;
        ecs::Manager _ecsMgr;

        std::shared_ptr<network::UdpSocket> _udpSocket;
        network::MyRfcServer<network::UdpSocket> _rfcMgr;
        std::map<int, UserInfo> _playerFd;
        uint8_t _nbPlayers { 1 };
        bool _isRunning { true };
    };
}