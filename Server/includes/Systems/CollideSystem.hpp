//
// Created by nhyarlathotep on 24/11/18.
//

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "../GameComponents.hpp"
#include "../GameEvents.hpp"

class CollideSystem : public ecs::System {
public:
    explicit CollideSystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr), _evtMgr(evtMgr) {
        setNeededComponent({ Player::m_type, MovableHitBox::m_type, TeamComponent::m_type });
        setNeededComponent({ Monster::m_type, MovableHitBox::m_type, TeamComponent::m_type });
        setNeededComponent({ Missile::m_type, MovableHitBox::m_type, TeamComponent::m_type });
    }

    /**
     * @brief Check collide between two entities
     * @param it [in] Missile ECS identifier
     * @param other [in] Other ECS identifier
     * @return boolean [out] If missile collide
     */
    bool missileCollide(ecs::Entity it, ecs::Entity other) {
        const auto &missile { m_manager.getComponentManager<Missile>().getComponent(it) };
        const auto &missileTeam { m_manager.getComponentManager<TeamComponent>().getComponent(it) };
        const auto &missileHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
        const auto &otherTeam { m_manager.getComponentManager<TeamComponent>().getComponent(other) };
        const auto &otherHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(other) };

        if (missileTeam._team != otherTeam._team && missileHitBox.checkCollide(otherHitBox)) {
            /* Collide */
            if (m_manager.getComponentManager<Monster>().hasEntity(other)) {
                /* Handle Monster */
                _evtMgr.emit<Game::CollideEvent>(it, other, missile._charge + 1);
            } else if (m_manager.getComponentManager<Player>().hasEntity(other)) {
                auto &player { m_manager.getComponentManager<Player>().getComponent(other) };
                m_manager.removeEntity(it); /* Remove Missile */
                _evtMgr.emit<Game::RemoveEvent>(it);
                if (player._shield == 0) {
                    /* Remove Player */
                    m_manager.removeEntity(other);
                    _evtMgr.emit<Game::RemoveEvent>(other, true);
                } else if (--player._shield == 0)
                    _evtMgr.emit<Game::RemoveEvent>(player._shieldEntity);
            }
            return true;
        }
        return false;
    }

    /**
     * @brief Checks for collisions between entities.
     * @param timeSinceLastFrame [in] Elapsed time.
     * @param it [in] Entity
     */
    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {
        for (auto &other : m_entities) {
            if (m_manager.getComponentManager<Missile>().hasEntity(it) && missileCollide(it, other)) {
                return;
            } else if (m_manager.getComponentManager<Player>().hasEntity(it)) {
                if (m_manager.getComponentManager<Monster>().hasEntity(other)) {
                    auto &a { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
                    auto &b { m_manager.getComponentManager<MovableHitBox>().getComponent(other) };
                    if (a.checkCollide(b)){
                        /* Remove Player */
                        m_manager.removeEntity(it);
                        _evtMgr.emit<Game::RemoveEvent>(it, true);
                        break ;
                    }
                }
            }
        }
    }

private:
    EventManager &_evtMgr;
};