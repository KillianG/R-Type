//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "../GameComponents.hpp"
#include "../GameEvents.hpp"

class DrawSystem : public ecs::System {
public:
    DrawSystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr), _evtMgr(evtMgr) {
        setNeededComponent({ Player::m_type, MovableHitBox::m_type, TeamComponent::m_type, /*EntityType::m_type*/});
        setNeededComponent({ Monster::m_type, MovableHitBox::m_type, TeamComponent::m_type, /*EntityType::m_type*/});
        setNeededComponent({ Missile::m_type, MovableHitBox::m_type, TeamComponent::m_type, /*EntityType::m_type*/});
    }

    void updateEntities(float timeSinceLastFrame) override {
        Game::DrawEvent evt {};
        for (auto &it : m_entities) {
            auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
            evt._entities.emplace_back(it, hitBox._spriteType, hitBox.addTime(timeSinceLastFrame), hitBox._pos.x, hitBox._pos.y);
        }
        _evtMgr.emit<Game::DrawEvent>(std::move(evt));
    }

    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {}
private:
    EventManager &_evtMgr;
};
