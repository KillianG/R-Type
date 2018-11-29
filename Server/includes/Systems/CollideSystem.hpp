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
     * @tparam Component
     * @param it [in] Missile ECS identifier
     * @param other [in] Other ECS identifier
     * @return boolean [out] If missile collide
     */
    template <typename Component>
    bool missileCollide(ecs::Entity it, ecs::Entity other) {
        const auto &missile { m_manager.getComponentManager<Missile>().getComponent(it) };
        const auto &missileTeam { m_manager.getComponentManager<TeamComponent>().getComponent(it) };
        const auto &missileHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
        const auto &otherTeam { m_manager.getComponentManager<TeamComponent>().getComponent(other) };
        const auto &otherHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(other) };

        if (missileTeam._team != otherTeam._team && missileHitBox.checkCollide(otherHitBox)) {
            /* Collide */
            if (missile._charge < 3) {
                m_manager.removeEntity(it); /* Remove Missile */
                _evtMgr.emit<Game::RemoveEvent>(it);
            }
            m_manager.removeEntity(other); /* Remove entity */
            _evtMgr.emit<Game::RemoveEvent>(other, true);
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
            if (m_manager.getComponentManager<Missile>().hasEntity(it)) {
                if (m_manager.getComponentManager<Player>().hasEntity(other) && missileCollide<Player>(it, other)) /* Missile X Player */
                    break;
                else if (m_manager.getComponentManager<Monster>().hasEntity(other) && missileCollide<Monster>(it, other)) /* Missile X Monster */
                    break;
            }
        }
    }

private:
    EventManager &_evtMgr;
};