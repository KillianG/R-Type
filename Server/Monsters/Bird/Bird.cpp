//
// Created by nhyarlathotep on 25/11/18.
//

#include "Bird.hpp"

extern "C" {
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Bird>(); }
    std::string getName() {return "Bird";}
    network::EntityInfo getInit() { return network::EntityInfo(EnnemyConfig::BIRD, EnnemyConfig::EnnemySprite.at(EnnemyConfig::BIRD), EnnemyConfig::EnnemyHitboxes.at(EnnemyConfig::BIRD));}
};

const Game::vector2f &Bird::move(float timeSinceLastFrame) noexcept {
    if (_phase) {
        _pos.translate(_dir.x * timeSinceLastFrame, -_speedMonster * timeSinceLastFrame);
        if (_pos.y < _basePosY - 50)
            _phase = false;
    } else {
        _pos.translate(_dir.x * timeSinceLastFrame, _speedMonster * timeSinceLastFrame);
        if (_pos.y > _basePosY + 50)
            _phase = true;
    }
    return _pos;
}

MovableHitBox Bird::initEnnemy(const Game::vector2f &pos) noexcept
{
    _pos = pos;
    _basePosY = pos.y;
    return { EnnemyConfig::EnnemyHitboxes.at(EnnemyConfig::BIRD), pos, EnnemyConfig::BIRD, EnnemyConfig::EnnemyAnimSize.at(EnnemyConfig::BIRD) };
}
