//
// Created by nhyarlathotep on 27/11/18.
//

#pragma once

#include <map>
#include <random>
#include <Server/includes/DynamicLoaderManager.hpp>
#include "../../../libs/GFX/Singleton.hpp"
#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "../../levelParsing/ParsingLevel.hpp"
#include "../GameEvents.hpp"
#include "../GameComponents.hpp"
#include "../DynamicLoader.hpp"

class EnnemySystem : public ecs::System, public Receiver<EnnemySystem> {
public:
    explicit EnnemySystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr), _evtMgr(evtMgr), _loader(gfx::Singleton<game::DynamicLoaderManager>::get()), _endGame(false){
        evtMgr.subscribe<Game::RemoveEvent>(*this);
        evtMgr.subscribe<Game::CollideEvent>(*this);

        setNeededComponent({ Monster::m_type, MovableHitBox::m_type, TeamComponent::m_type });

        _parsingLevel.startGame();
    }

    void updateEntities(float timeSinceLastFrame) override {
        auto &&monsters = _parsingLevel.getMonster(timeSinceLastFrame);

        if (monsters.empty() && m_entities.empty() && _parsingLevel.isEnd() && !_endGame) {
            if (!_parsingLevel.setStreamLevel(_parsingLevel.getLevel() + 1)) {
                Logger::log(Logger::LogType::warn, std::string("NO MORE LEVEL AVAILABLE: ") + std::to_string(_parsingLevel.getLevel()));
                _parsingLevel.setStreamLevel(1);
                monsters = _parsingLevel.getMonster(timeSinceLastFrame);
            } else {
                Logger::log(Logger::LogType::info, std::string("Next Level : ") + std::to_string(_parsingLevel.getLevel()));
                monsters = _parsingLevel.getMonster(timeSinceLastFrame);
            }
        }

        for (auto &monster : monsters){
            auto entity{ m_manager.createEntity() };
            if (!monster._endGame)
                _monstersList[entity] = { _loader.getMonster(monster._type) };
            if (_monstersList[entity] == nullptr){
                _monstersList.erase(_monstersList.find(entity));
                continue ;
            }
            m_manager.addComponent<Monster>(entity, Monster(entity));
            m_manager.addComponent<TeamComponent>(entity, TeamComponent(Game::Team::ennemy));
            m_manager.addComponent<MovableHitBox>(entity, _monstersList[entity]->initEnnemy(monster._pos));
            m_manager.registerEntity(entity);
        }

        for (auto &it : m_entities) {
            updateEntity(timeSinceLastFrame, it);
        }
    }

    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {
        auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
        hitBox._pos = _monstersList[it]->update(timeSinceLastFrame);

        /* Spawn Missiles */
        if (_monstersList[it]->shootMissile()) {
            auto &&list { _monstersList[it]->shootMissiles() };
            for (auto &missile : list) {
                missile._id = it;
                _evtMgr.emit<Game::ShootEvent>(missile);
            }
        }

        /* Spawn Ennemies */
        if (_monstersList[it]->spawnEnnemy()) {
            auto &&list { _monstersList[it]->spawnEnnemies() };
            for (auto &ennemy : list) {
                auto entity{ m_manager.createEntity() };
                _monstersList[entity] = { _loader.getMonster(ennemy._type) };
                if (_monstersList[entity] == nullptr) {
                    _monstersList.erase(_monstersList.find(entity));
                    continue ;
                }
                m_manager.addComponent<Monster>(entity, Monster(entity));
                m_manager.addComponent<TeamComponent>(entity, TeamComponent(Game::Team::ennemy));
                m_manager.addComponent<MovableHitBox>(entity, _monstersList[entity]->initEnnemy(ennemy._pos));
                m_manager.registerEntity(entity);
            }
        }
    }

    void receive(const Game::RemoveEvent &event) {
        if (_monstersList.find(event._id) != _monstersList.end()) {
            if (event._death) {
                std::random_device random_device;
                std::mt19937 engine{random_device()};
                std::uniform_int_distribution<size_t> dist(1, 100);
                size_t value = dist(engine);
                if (value <= 15) {
                    auto &&entity { m_manager.createEntity() };
                    auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(event._id) };

                    if (value % 2 == 0) {
                        m_manager.addComponent<PowerUpSpeed>(entity, PowerUpSpeed(80));
                        m_manager.addComponent<MovableHitBox>(entity, MovableHitBox({34, 36}, hitBox._pos, 14, 12, 0.05));
                    } else {
                        m_manager.addComponent<PowerUpShield>(entity, PowerUpShield());
                        m_manager.addComponent<MovableHitBox>(entity, MovableHitBox({34, 36}, hitBox._pos, 15, 12, 0.05));
                    }
                    m_manager.registerEntity(entity);
                }

                /* Spawn Missiles */
                if (_monstersList[event._id]->shootMissileOnDeath()) {
                    auto &&list { _monstersList[event._id]->shootMissilesOnDeath() };
                    for (auto &missile : list) {
                        missile._id = event._id;
                        _evtMgr.emit<Game::ShootEvent>(missile);
                    }

                }
                m_manager.removeEntity(event._id); /* Remove entity */
            }
            _monstersList.erase(event._id);
        }
    }

    /**
     * Receive Collide between player's Missile and a Monster
     * @param event [in] Collide infos
     */
    void receive(const Game::CollideEvent &event) {
        if (_monstersList.find(event._other) != _monstersList.end() && !_monstersList[event._other]->takeHit(event._charge)) {
            /* Kill other entity */
            _evtMgr.emit<Game::RemoveEvent>(event._other, true);
            if (event._charge < 4) {
                _evtMgr.emit<Game::RemoveEvent>(event._id);
                m_manager.removeEntity(event._id);
            }
        } else {
            /* Remove Missile */
            m_manager.removeEntity(event._id);
            _evtMgr.emit<Game::RemoveEvent>(event._id);
        }
    }

private:
    EventManager &_evtMgr;
    Game::ParsingLevel _parsingLevel;
    game::DynamicLoaderManager &_loader;
    std::map<ecs::Entity, IEnnemy::Ptr> _monstersList;

    bool _endGame;
};