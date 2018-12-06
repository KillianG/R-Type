/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "GameComponents.hpp"
#include "GameEvents.hpp"

class BonusSystem : public ecs::System {
public:
    explicit BonusSystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr), _evtMgr(evtMgr) {
        setNeededComponent({Player::m_type, MovableHitBox::m_type});
        setNeededComponent({PowerUpSpeed::m_type, MovableHitBox::m_type});
        setNeededComponent({PowerUpShield::m_type, MovableHitBox::m_type});
    }

    /**
     * @brief Gives player some speed
     * @param it [int] bonus entity
     */
    void handlePowerUpSpeed(ecs::Entity it) {
        const auto &elemS { m_manager.getComponentManager<PowerUpSpeed>().getComponent(it) };

        for (auto &elem : m_entities) {
            if (m_manager.getComponentManager<Player>().hasEntity(elem)) {
                auto &player { m_manager.getComponentManager<Player>().getComponent(elem) };
                auto &sHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
                auto &pHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(elem) };

                if (pHitBox.checkCollide(sHitBox)) {
                    player += elemS;
                    m_manager.removeEntity(it);
                    _evtMgr.emit<Game::RemoveEvent>(it);
                    break;
                }
            }
        }
    };

    /**
     * @brief Gives a shield to the player
     * @param it [int] bonus entity
     */
    void handlePowerUpShield(ecs::Entity it) {
        for (auto &elem : m_entities) {
            if (m_manager.getComponentManager<Player>().hasEntity(elem)) {
                auto &player { m_manager.getComponentManager<Player>().getComponent(elem) };
                auto &sHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
                auto &pHitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(elem) };

                if (pHitBox.checkCollide(sHitBox)) {
                    player._shield += 1;
                    m_manager.removeEntity(it);
                    _evtMgr.emit<Game::RemoveEvent>(it);
                    break;
                }
            }
        }
    }

    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {
        if (m_manager.getComponentManager<PowerUpSpeed>().hasEntity(it))
            handlePowerUpSpeed(it);
        else if (m_manager.getComponentManager<PowerUpShield>().hasEntity(it))
            handlePowerUpShield(it);
    }

private:
    EventManager &_evtMgr;
};