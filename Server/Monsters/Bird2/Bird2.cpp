//
// Created by nhyarlathotep on 25/11/18.
//

#include "Bird2.hpp"


extern "C" {
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Bird2>(); }
    std::string getName() {return "Bird2";}
    network::EntityInfo getInit() { return network::EntityInfo(EnnemyConfig::BIRD2, EnnemyConfig::EnnemySprite.at(EnnemyConfig::BIRD2), EnnemyConfig::EnnemyHitboxes.at(EnnemyConfig::BIRD2));}
};

const Game::vector2f &Bird2::move(float timeSinceLastFrame) noexcept {
    if (_phase) {
        _pos.translate(_dir.x * timeSinceLastFrame, -_speedMonster * timeSinceLastFrame);
        if (_pos.y <  50)
            _phase = false;
    } else {
        _pos.translate(_dir.x * timeSinceLastFrame, _speedMonster * timeSinceLastFrame);
        if (_pos.y >  720 - 30)
            _phase = true;
    }
    return _pos;
}

MovableHitBox Bird2::initEnnemy(const Game::vector2f &pos) noexcept
{
    _pos = pos;
    return { EnnemyConfig::EnnemyHitboxes.at(EnnemyConfig::BIRD2), pos, EnnemyConfig::BIRD2, EnnemyConfig::EnnemyAnimSize.at(EnnemyConfig::BIRD2) };
}
