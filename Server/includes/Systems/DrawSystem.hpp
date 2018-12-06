//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include "../../../libs/ECS/Manager.hpp"
#include "../../libs/Network/socket/include/UdpSocket.hpp"
#include "../../libs/Network/RFC/MyRfcServer.hpp"
#include "../GameComponents.hpp"
#include "../GameEvents.hpp"
#include "GameConfig.hpp"

class DrawSystem : public ecs::System {
public:
    DrawSystem(ecs::Manager &ecsMgr, network::MyRfcServer<network::UdpSocket> &rfcMgr) : System(ecsMgr), _rfcMgr(rfcMgr) {
        setNeededComponent({ Player::m_type, MovableHitBox::m_type, TeamComponent::m_type });
        setNeededComponent({ Monster::m_type, MovableHitBox::m_type, TeamComponent::m_type });
        setNeededComponent({ Missile::m_type, MovableHitBox::m_type, TeamComponent::m_type });
        setNeededComponent({ PowerUpSpeed::m_type, MovableHitBox::m_type});
        setNeededComponent({ PowerUpShield::m_type, MovableHitBox::m_type});

        /* Background */
        _backgrounds.emplace_back(m_manager.createEntity(), 0, 0, 0, 0);
        _backgrounds.emplace_back(m_manager.createEntity(), 11, 0, 340, -135);
        _backgrounds.emplace_back(m_manager.createEntity(), 12, 0, 1000, 320);
        /* Star fields */
        _backgrounds.emplace_back(m_manager.createEntity(), 13, 0, 500, -200);
        _backgrounds.emplace_back(m_manager.createEntity(), 13, 0, 1780, 0);
        _backgrounds.emplace_back(m_manager.createEntity(), 13, 0, 300, 320);
    }

    void updateBackground() {
        _backgrounds[1].X -= 0.005f;    /* Sun */
        _backgrounds[2].X -= 0.04f;     /* Earth */
        _backgrounds[3].X -= 1.5f;      /* Starfield */
        _backgrounds[4].X -= 2.0f;      /* Starfield */
        _backgrounds[5].X -= 2.0f;      /* Starfield */

        for (auto &it : _backgrounds) {
            if (it.X < -Config::width / 2.0f)
                it.X = Config::width;
        }
    }

    void updateEntities(float timeSinceLastFrame) override {
        std::vector<network::EntityPos> drawable;

        updateBackground();
        drawable.insert( drawable.end(), _backgrounds.begin(), _backgrounds.end() );
        for (auto &it : m_entities) {
            auto &hitBox { m_manager.getComponentManager<MovableHitBox>().getComponent(it) };
            drawable.emplace_back(it, hitBox._spriteType, hitBox.addTime(timeSinceLastFrame), hitBox._pos.x, hitBox._pos.y);

            /* Draw Shield*/
            if (m_manager.getComponentManager<Player>().hasEntity(it)) {
                const auto &player { m_manager.getComponentManager<Player>().getComponent(it) };
                if (player._shield > 0)
                    drawable.emplace_back(player._shieldEntity, 16, 0, hitBox._pos.x - 5, hitBox._pos.y - 8);
            }
        }
        _rfcMgr.entitiesPos(std::move(drawable));
    }

    void updateEntity(float timeSinceLastFrame, ecs::Entity it) override {}
private:
    network::MyRfcServer<network::UdpSocket> &_rfcMgr;
    std::vector<network::EntityPos> _backgrounds;
};
