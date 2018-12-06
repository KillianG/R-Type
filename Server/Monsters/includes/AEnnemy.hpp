//
// Created by nhyarlathotep on 29/11/18.
//

#pragma once

#include "IEnnemy.hpp"

class AEnnemy : public IEnnemy {
public:
    explicit AEnnemy(EnnemyConfig::EnnemySpriteId id, int hp = 1) : _hp(hp), _spriteId(id){}

    network::EntityInfo getInit() noexcept override {
        return { _spriteId, EnnemyConfig::EnnemySprite.at(_spriteId), EnnemyConfig::EnnemyHitboxes.at(_spriteId) };
    }

    bool shootMissile() noexcept override { return _isShooting; };

    bool shootMissileOnDeath() noexcept override { return _isShootingOnDeath; };

    std::vector<Game::ShootEvent> shootMissilesOnDeath() override { return std::vector<Game::ShootEvent>(); };

    bool spawnEnnemy() const noexcept override { return _isSpawning; };

    bool takeHit(int charge) noexcept override {
        if (_indestructible)
            return true;
        _hp -= charge;
        return _hp > 0;
    }

protected:
    MovableHitBox init(const Game::vector2f &pos) noexcept {
        _pos = pos;
        return { EnnemyConfig::EnnemyHitboxes.at(_spriteId), pos, _spriteId, EnnemyConfig::EnnemyAnimSize.at(_spriteId) };
    };

    int _hp;
    bool _isShooting { false };
    bool _isSpawning { false };
    bool _indestructible { false };
    bool _isShootingOnDeath { false };
    Game::vector2f _pos;
    EnnemyConfig::EnnemySpriteId _spriteId;
};