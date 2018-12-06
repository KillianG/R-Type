//
// Created by nhyarlathotep on 24/11/18.
//

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "GameComponents.hpp"
#include "GameEvents.hpp"
#include "GameConfig.hpp"

class ShootSystem : public ecs::System, public Receiver<ShootSystem> {
public:
    explicit ShootSystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr) {
        evtMgr.subscribe<Game::ShootEvent>(*this);

        setNeededComponent({ Player::m_type, MovableHitBox::m_type, TeamComponent::m_type });
        setNeededComponent({ Monster::m_type, MovableHitBox::m_type, TeamComponent::m_type });
        setNeededComponent({ Missile::m_type, MovableHitBox::m_type, TeamComponent::m_type });
    }

    /**
     * @brief Moves missiles
     * @param timeSinceLastFrame [in] Elapsed time
     * @param it [in] Entity
     */
    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {
        if (m_manager.getComponentManager<Missile>().hasEntity(it)) {
            auto &missile { m_manager.getComponentManager<Missile>().getComponent(it) };
            auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
            hitBox._pos.translate(missile._dir.x * timeSinceLastFrame, missile._dir.y * timeSinceLastFrame);
        }
    }

    /**
     * @brief Detects if an entity shot
     * @param evt [in] Defines the shot (Missile)
     */
    void receive(const Game::ShootEvent &evt) {
        auto newMissile { m_manager.createEntity() };
        auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(evt._id) };

        if (m_manager.getComponentManager<Player>().hasEntity(evt._id)) {
            m_manager.addComponent<MovableHitBox>(newMissile, MovableHitBox(Config::missileHitBoxes[evt._charge], {hitBox._pos.x + hitBox._dims.width / 2.0f, hitBox._pos.y + hitBox._dims.height / 2.0f - Config::missileHitBoxes[evt._charge].height / 2}, 5 + evt._charge, 2));
        } else if (m_manager.getComponentManager<Monster>().hasEntity(evt._id)) {
            m_manager.addComponent<MovableHitBox>(newMissile, MovableHitBox({17, 14}, {hitBox._pos.x, hitBox._pos.y + hitBox._dims.height / 2.0f - 14 / 2}, 10, 8));
        }
        m_manager.addComponent<Missile>(newMissile, Missile(evt._charge, evt._dir));
        m_manager.addComponent<TeamComponent>(newMissile, TeamComponent(evt._team));
        m_manager.registerEntity(newMissile);
    }
};
