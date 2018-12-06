//
// Created by nhyarlathotep on 24/11/18.
//

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../../libs/EventManager/EventManager.hpp"
#include "GameComponents.hpp"
#include "GameEvents.hpp"
#include "GameConfig.hpp"

class PlayerSystem : public ecs::System, public Receiver<PlayerSystem> {
public:
    explicit PlayerSystem(ecs::Manager &ecsMgr, EventManager &evtMgr) : System(ecsMgr) {
        evtMgr.subscribe<Game::MoveEvent>(*this);

        setNeededComponent({ Player::m_type, MovableHitBox::m_type });
    }

    /**
     * @brief Moves entities depending on their directions.
     * @param timeSinceLastFrame [in] Elapsed time
     * @param it [in] Entity
     */
    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {
        auto &player { m_manager.getComponentManager<Player>().getComponent(it) };

        if (player._dir.x != 0 || player._dir.y != 0) {
            auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
            /* Move Players */
            hitBox._pos.translate((player._dir.x) * timeSinceLastFrame, (player._dir.y) * timeSinceLastFrame);
            /* Check Out of bounds */
            if (hitBox._pos.x < 0 || hitBox._pos.x + hitBox._dims.width > Config::width)
                hitBox._pos.translate(-player._dir.x * timeSinceLastFrame, 0);
            if (hitBox._pos.y < 0 || hitBox._pos.y + hitBox._dims.height > Config::height)
                hitBox._pos.translate(0, -player._dir.y * timeSinceLastFrame);
            player._dir = {0, 0};
        }
        /* Decrease Speed Bonus */
        if (player._speed > 0)
            player._speed -= (timeSinceLastFrame * 0.2f);
    }

    /**
     * @brief Sets direction of a player
     * @param evt [in] Defines which player has to move.
     */
    void receive(const Game::MoveEvent &evt) {
        for (auto &it : m_entities) {
            auto &player { m_manager.getComponentManager<Player>().getComponent(it) };
            if (player._id == evt._id) {
                switch (evt._dir) {
                    case (Game::MovementDir::left) :
                        player._dir.x = -Config::speed -player._speed;
                        break;
                    case (Game::MovementDir::right) :
                        player._dir.x = Config::speed + player._speed;
                        break;
                    case (Game::MovementDir::up) :
                        player._dir.y = -Config::speed - player._speed;
                        break;
                    case (Game::MovementDir::down) :
                        player._dir.y = +Config::speed + player._speed;
                        break;
                    default:
                        break;
                }
                return;
            }
        }
    }
};