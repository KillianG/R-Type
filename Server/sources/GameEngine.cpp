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
const ecs::ComponentType PowerUpShield::m_type = 7;
const ecs::ComponentType PowerUpSpeed::m_type = 8;

namespace Game {
    GameEngine::GameEngine(std::shared_ptr<network::UdpSocket> &udpSocket) : _udpSocket(udpSocket), _rfcMgr(*_udpSocket) {
        Config::initConfig();
        _evtMgr.subscribe<RemoveEvent>(*this);

        _ecsMgr.createComponentManager<Player>();
        _ecsMgr.createComponentManager<Missile>();
        _ecsMgr.createComponentManager<Monster>();
        _ecsMgr.createComponentManager<MovableHitBox>();
        _ecsMgr.createComponentManager<TeamComponent>();
        _ecsMgr.createComponentManager<EntityType>();
        _ecsMgr.createComponentManager<PowerUpShield>();
		_ecsMgr.createComponentManager<PowerUpSpeed>();
        _ecsMgr.addSystem(ecs::System::Ptr(std::make_shared<EnnemySystem>(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(std::make_shared<PlayerSystem>(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(std::make_shared<OutBorders>(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(std::make_shared<ShootSystem>(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(std::make_shared<CollideSystem>(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(std::make_shared<BonusSystem>(_ecsMgr, _evtMgr)));
        _ecsMgr.addSystem(ecs::System::Ptr(std::make_shared<DrawSystem>(_ecsMgr, _rfcMgr)));
    }

    void GameEngine::receive(const RemoveEvent &event) {
        if (event._death)
            _rfcMgr.sendDead(event._id);
        else
            _rfcMgr.sendRemove(event._id);
    }

    ecs::Entity GameEngine::addPlayer() {
        auto entity{ _ecsMgr.createEntity() };

        _ecsMgr.addComponent<Player>(entity, Player(entity, _ecsMgr.createEntity()));
        _ecsMgr.addComponent<TeamComponent>(entity, TeamComponent(Team::ally));
        _ecsMgr.addComponent<MovableHitBox>(entity, MovableHitBox(Config::playerHitBox, {100, (Config::height / 5.0f) * _nbPlayers}, _nbPlayers, 8));
        _ecsMgr.registerEntity(entity);
        _nbPlayers++;
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

        if (std::regex_match(req.data, match, connect)) {
            auto elem = std::find_if(_playerFd.begin(), _playerFd.end(), [ip](auto &elem){return elem.second._ip == ip;});
            if (elem != _playerFd.end() && elem->first != req.sender) {
                std::cout << "find player" << std::endl;
                _playerFd[req.sender] = {elem->second._id, elem->second._ip};
                _playerFd.erase(elem);
            } else if (_playerFd.find(req.sender) == _playerFd.end()) {
                _playerFd[req.sender] = {addPlayer(), _udpSocket->getIp(req.sender)};
            }
            _rfcMgr.entitiesInit(Config::allEntityInit, req.sender);
        }else if (std::regex_match(req.data, match, move)) {
            _evtMgr.emit<MoveEvent>(_playerFd[req.sender]._id, _rfcMgr.getPlayerMove(match[1].str()));
        } else if (std::regex_match(req.data, match, fireCharging)) {
            //std::cout << req.data << std::endl;
            //_evtMgr.emit<ChargeEvent>();
        } else if (std::regex_match(req.data, match, fire)) {
            std::regex_search(req.data, match, fire);
            Game::vector2f dir { Config::missileSpeed, 0 };
            _evtMgr.emit<ShootEvent>(_playerFd[req.sender]._id, Team::ally, std::stoi(match[1]), std::move(dir));
        } else
            throw rtype::Exception("rfc not recognize: " + req.data);
    }

    /**
     * @brief Game Loop of 60 fps
     */
    void GameEngine::run() {
        float timeSinceLastFrame { 0 };
        std::chrono::nanoseconds lag { 0 };
        std::chrono::nanoseconds timeStep { Config::_60fps };
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
    }

    void GameEngine::stopGame() noexcept {
        _isRunning = false;
    }
}
