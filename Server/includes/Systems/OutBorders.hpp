//
// Created by nhyarlathotep on 24/11/18.
//

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "GameComponents.hpp"
#include "GameEvents.hpp"
#include "GameConfig.hpp"

class OutBorders : public ecs::System {
public:
    explicit OutBorders(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr), _evtMgr(evtMgr) {
        setNeededComponent({ MovableHitBox::m_type });
    }

    /**
     * @brief Removes entity if it position is out of the defined borders
     * @param timeSinceLastFrame [in] Elapsed time
     * @param it [in] Entity
     */
    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {
        auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };

        if ((hitBox._pos.x < -hitBox._dims.width || hitBox._pos.x > Config::width) ||
            (hitBox._pos.y < -hitBox._dims.height || hitBox._pos.y > Config::height)) {
            /* OutOfBorders */
            m_manager.removeEntity(it);
            _evtMgr.emit<Game::RemoveEvent>(it);
        }
    }

private:
    EventManager &_evtMgr;
};