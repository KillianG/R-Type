//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "../../../libs/Network/networkUtils.hpp"
#include "../../includes/GameComponents.hpp"
#include "../../includes/Utils.hpp"

class IEnnemy {
public:
    using Ptr = std::unique_ptr<IEnnemy>;

    virtual MovableHitBox initEnnemy(const Game::vector2f &) noexcept = 0;

    virtual ~IEnnemy() = default;

    virtual const Game::vector2f &move(float) noexcept = 0;
};

extern "C" {
    IEnnemy::Ptr getMonsterLibrary();
    std::string getName();
    network::EntityInfo getInit();
}

namespace EnnemyConfig {
    enum EnnemySpriteId : size_t {
        BIRD = 10,
        BIRD2 = 10
    };

    const std::unordered_map<EnnemySpriteId, size_t> EnnemyAnimSize{
            {BIRD, 8},
    };

    const std::unordered_map<EnnemySpriteId, Game::box> EnnemyHitboxes{
            {BIRD, {33, 36}},
    };

    const std::unordered_map<EnnemySpriteId, std::string> EnnemySprite{
            {BIRD, "ennemy1_33x36"},
    };
}