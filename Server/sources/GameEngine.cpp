//
// Created by nhyarlathotep on 20/11/18.
//

#include <chrono>
#include <algorithm>
#include "GameConfig.hpp"
#include "../includes/GameEngine.hpp"
#include "../includes/GameSystems.hpp"

const ecs::ComponentType Player::m_type = 1;
const ecs::ComponentType Missile::m_type = 2;
const ecs::ComponentType Monster::m_type = 3;
const ecs::ComponentType TeamComponent::m_type = 4;
const ecs::ComponentType MovableHitBox::m_type = 5;
const ecs::ComponentType EntityType::m_type = 6;

namespace Game {
    GameEngine::GameEngine(std::shared_ptr<network::UdpSocket> &udpSocket) : _udpSocket(udpSocket), _rfcMgr(*_udpSocket) {
        Config::initConfig();
        _evtMgr.subscribe<DrawEvent>(*this);
        _evtMgr.subscribe<RemoveEvent>(*this);


        _ecsMgr.createComponentManager<Player>();
        _ecsMgr.createComponentManager<Missile>();
        _ecsMgr.createComponentManager<Monster>();
        _ecsMgr.createComponentManager<MovableHitBox>();
        _ecsMgr.createComponentManager<TeamComponent>();
        _ecsMgr.createComponentManager<EntityType>();
        _ecsMgr.addSystem(ecs::System::Ptr(new OutBorders(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(new EnnemySystem(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(new PlayerSystem(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(new ShootSystem(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(new CollideSystem(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(new DrawSystem(_ecsMgr, _evtMgr)));
    }

    /**
     * @brief
     * @param event
     */
    void GameEngine::receive(const DrawEvent &event) {
	    _rfcMgr.entitiesPos(event._entities);
    }

    /**
     * @brief
     * @param event
     */
    void GameEngine::receive(const RemoveEvent &event) {
        if (event._death)
            _rfcMgr.sendDead(event._id);
        else
            _rfcMgr.sendRemove(event._id);
    }

    /**
     * @brief Create a new player
     */
    ecs::Entity GameEngine::addPlayer() {
        auto entity{ _ecsMgr.createEntity() };

        _ecsMgr.addComponent<Player>(entity, Player(entity));
        _ecsMgr.addComponent<TeamComponent>(entity, TeamComponent(Team::ally));

        auto hitBox { MovableHitBox(Config::playerHitBox, {100, (Config::height / 5.0f) * _nbPlayers}, _nbPlayers, 8) };
        _ecsMgr.addComponent<MovableHitBox>(entity, hitBox);
        _ecsMgr.registerEntity(entity);
        Logger::log(Logger::LogType::debug, "Create Player [" + std::to_string(_nbPlayers++) + "] at [" + std::to_string(hitBox._pos.x) + "][" + std::to_string(hitBox._pos.y) + "]");

        return entity;
    }

    /**
     * function that manage request send to the game
     * Move player
     * Player charge fire
     * Player Shoot
     */
    void GameEngine::manageRequest() {
        auto req = _rfcMgr.getLastRequest();
        if (req.data == "PING\r\n")
            return;
        std::regex move("MOVE (UP|LEFT|DOWN|RIGHT)\r\n");
        std::regex fireCharging("FIRE CHARGING ([0-4])\r\n");
        std::regex fire("FIRE SHOT ([0-4])\r\n");
        std::regex connect("CONNECT ([a-zA-Z0-9]+)\r\n");

        std::smatch match {};
        auto ip = _udpSocket->getIp(req.sender);


        if (std::regex_match(req.data, match, connect) &&  std::find_if(_playerFd.begin(), _playerFd.end(), [ip](auto &elem){std::cout << ip << " " << elem.second._ip; return elem.second._ip == ip;}) != _playerFd.end()) {
            auto elem = std::find_if(_playerFd.begin(), _playerFd.end(), [ip](auto &elem){return elem.second._ip == ip;});
            _playerFd[req.sender] = elem->second;
            _playerFd.erase(elem);
            _rfcMgr.entitiesInit(Config::allEntityInit, req.sender);
        }
        else if (std::regex_match(req.data, match, connect) &&  _playerFd.find(req.sender) == _playerFd.end()) {
            _playerFd[req.sender] = {addPlayer(), _udpSocket->getIp(req.sender)};
            _rfcMgr.entitiesInit(Config::allEntityInit, req.sender);
        } else if (std::regex_match(req.data, match, move)) {
            _evtMgr.emit<MoveEvent>(_playerFd[req.sender]._id, _rfcMgr.getPlayerMove(match[1].str()));
        } else if (std::regex_match(req.data, match, fireCharging)) {
            //std::cout << req.data << std::endl;
            //_evtMgr.emit<ChargeEvent>();
        } else if (std::regex_match(req.data, match, fire)) {
            std::regex_search(req.data, match, fire);
            _evtMgr.emit<ShootEvent>(_playerFd[req.sender]._id, Team::ally, std::stoi(match[1]));
        } else
            throw rtype::Exception("rfc not recognize: " + req.data);
    }

    /**
     * @brief Game Loop of 60 fps
     */
    void GameEngine::run() {
        float timeSinceLastFrame { 0 };
        std::chrono::nanoseconds lag { 0 };
        std::chrono::nanoseconds timeStep { Config::_120fps };
        clock::time_point start{ clock::now() };

        while (_isRunning) {
            auto deltaTime = clock::now() - start;
            start = clock::now();
            lag += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);

            if (lag > timeStep) {
                timeSinceLastFrame = static_cast<float>(lag.count()) / 1000000000.0f; /*nano seconds to seconds*/
                _ecsMgr.updateSystems(timeSinceLastFrame);
                lag -= timeStep;
            }
            if (!_rfcMgr.requestIsEmpty())
                manageRequest();
        }
        Logger::log(Logger::LogType::info, "end of game loop");
    }

    void GameEngine::stopGame() noexcept {
        _isRunning = false;
    }
}
