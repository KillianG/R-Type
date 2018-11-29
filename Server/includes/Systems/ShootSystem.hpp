//
// Created by nhyarlathotep on 24/11/18.
//

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "../GameComponents.hpp"
#include "../GameEvents.hpp"


class ShootSystem : public ecs::System, public Receiver<ShootSystem> {
public:
    explicit ShootSystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr), _evtMgr(evtMgr) {
        _evtMgr.subscribe<Game::ShootEvent>(*this);

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
            auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
            auto &team { m_manager.getComponentManager<TeamComponent>().getComponent(it) };
            hitBox._pos.translate(((team._team == Game::Team::ally) ? Config::missileSpeed : -Config::missileSpeed) * timeSinceLastFrame, 0);
        }
    }

    /**
     * @brief Set the Missile at the shooter pos
     * @tparam Component The Shooter can be a Player / Monster
     * @param newMissile [in] Missile ECS identifier
     * @param it [in] Shooter ECS identifier
     * @param evt [in] ShootEvent
     * @return boolean [out] If missile is set
     */
    template <typename Component>
    bool shootFromEntity(ecs::Entity newMissile, ecs::Entity it, const Game::ShootEvent &evt) const {
        auto &shooterTeam { m_manager.getComponentManager<TeamComponent>().getComponent(it) };

        if (evt._team == shooterTeam._team) {
            auto &shooter { m_manager.getComponentManager<Component>().getComponent(it) };
            if (shooter._id == evt._id) {
                auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
                m_manager.addComponent<MovableHitBox>(newMissile, MovableHitBox(Config::missileHitBoxes[evt._charge], hitBox._pos, 5 + evt._charge, 2));
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Detects if an entity shot
     * @param evt [in] Defines the shot (Missile)
     */
    void receive(const Game::ShootEvent &evt) {
        auto newMissile { m_manager.createEntity() };
        for (auto &it : m_entities) {
            if (m_manager.getComponentManager<Player>().hasEntity(it) && shootFromEntity<Player>(newMissile, it, evt)) {
                /* Player shot */
                break;
            } else if (m_manager.getComponentManager<Monster>().hasEntity(it) && shootFromEntity<Monster>(newMissile, it, evt)) {
                /* Monster shot */
                break;
            }
        }
        m_manager.addComponent<Missile>(newMissile, Missile(evt._charge));
        m_manager.addComponent<TeamComponent>(newMissile, TeamComponent(evt._team));
        m_manager.registerEntity(newMissile);
    }

private:
    EventManager &_evtMgr;
};
