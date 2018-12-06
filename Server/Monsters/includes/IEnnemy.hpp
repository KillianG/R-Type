//
// Created by nhyarlathotep on 25/11/18.
//

#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "../../../libs/Network/networkUtils.hpp"
#include "../../includes/GameComponents.hpp"
#include "../../includes/GameEvents.hpp"
#include "MonsterInfo.hpp"

class IEnnemy {
public:
    using Ptr = std::unique_ptr<IEnnemy>;

    virtual MovableHitBox initEnnemy(const Game::vector2f &) noexcept = 0;

    virtual network::EntityInfo getInit() noexcept = 0;

    virtual bool takeHit(int) noexcept = 0;

    virtual bool shootMissile() noexcept = 0;

    virtual bool shootMissileOnDeath() noexcept = 0;

    virtual std::vector<Game::ShootEvent> shootMissiles() = 0;

    virtual std::vector<Game::ShootEvent> shootMissilesOnDeath() = 0;

    virtual bool spawnEnnemy() const noexcept = 0;

    virtual std::vector<Game::MonsterInfo> spawnEnnemies() = 0;

    virtual const Game::vector2f &update(float) noexcept = 0;

    virtual ~IEnnemy() = default;
};

extern "C" {
    std::string getName();
    IEnnemy::Ptr getMonsterLibrary();
}

namespace EnnemyConfig {
    enum EnnemySpriteId : size_t {
        BIRD = 20,
        BIRD2,
        BIRD3,
        LEAPER,
        LEAPER2,
        SHOOTER,
        METEORITE,
        FIRSTBOSS,
        ULTIMATRON
    };
    const std::unordered_map<EnnemySpriteId, size_t> EnnemyAnimSize {
            {BIRD, 8},
            {BIRD2, 8},
            {BIRD3, 8},
            {LEAPER, 16},
            {LEAPER2, 16},
            {SHOOTER, 8},
            {METEORITE, 19},
            {FIRSTBOSS, 3},
            {ULTIMATRON, 1},
    };

    const std::unordered_map<EnnemySpriteId, Game::box> EnnemyHitboxes {
            {BIRD, {66, 72}},
            {BIRD2, {66, 72}},
            {BIRD3, {66, 72}},
            {LEAPER, {66, 69}},
            {LEAPER2, {66, 69}},
            {SHOOTER, {66, 68}},
            {METEORITE, {72, 72}},
            {FIRSTBOSS, {155, 204}},
            {ULTIMATRON, {372, 720}},
    };

    const std::unordered_map<EnnemySpriteId, std::string> EnnemySprite {
            {BIRD, "Bird1"},
            {BIRD2, "Bird2"},
            {BIRD3, "Bird3"},

            {LEAPER, "Leaper1"},
            {LEAPER2, "Leaper2"},
            {SHOOTER, "Shooter1"},
            {METEORITE, "asteroid1"},
            {FIRSTBOSS, "FirstBoss"},
            {ULTIMATRON, "Ultimatron"},
    };
}
