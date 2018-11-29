//
// Created by nhyarlathotep on 19/11/18.
//

#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include "Utils.hpp"
#include "../../libs/EventManager/BaseEvent.hpp"
#include "../../libs/Network/networkUtils.hpp"
#include "../../libs/ECS/utiles.hpp"

namespace Game {

    /**
     * Defines the shooter
     */
    struct ShootEvent : public BaseEvent {
        ShootEvent(ecs::Entity &id, Team &&team, int charge = 0) : _id(id), _team(team), _charge(charge) {}

        ecs::Entity _id;
        Team _team;
        int _charge;
    };

    /**
     * no implemented yet
     */
    struct ChargeEvent : public BaseEvent {

    };

    /**
     * Defines who's moving and where
     */
    struct MoveEvent : public BaseEvent {
        MoveEvent(ecs::Entity &id, MovementDir &&dir) : _id(id), _dir(dir) {}

        ecs::Entity _id;
        MovementDir _dir { MovementDir::none };
    };

    /**
     * no implemented yet
     */
    struct BonusEvent : public BaseEvent {

    };

    /**
     * Defines who's dead
     */
    struct RemoveEvent : public BaseEvent {
        RemoveEvent(const ecs::Entity &id, bool death = false) : _id(id), _death(death) {}

        ecs::Entity _id;
        bool _death;
    };

    /**
     * Defines entities to draw
     */
    struct DrawEvent : public BaseEvent {
        std::vector<network::EntityPos> _entities;
    };
}
