//
// Created by nhyarlathotep on 25/11/18.
//

#include "FirsBoss.hpp"


extern "C" {
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<FirstBoss>(); }
    std::string getName() {return "FirstBoss";}
    network::EntityInfo getInit() { return network::EntityInfo(EnnemyConfig::BIRD2, EnnemyConfig::EnnemySprite.at(EnnemyConfig::BIRD2), EnnemyConfig::EnnemyHitboxes.at(EnnemyConfig::BIRD2));}
};

const Game::vector2f &FirstBoss::move(float timeSinceLastFrame) noexcept {
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

MovableHitBox FirstBoss::initEnnemy(const Game::vector2f &pos) noexcept
{
    _pos = pos;
    return { EnnemyConfig::EnnemyHitboxes.at(EnnemyConfig::BIRD), pos, EnnemyConfig::BIRD, EnnemyConfig::EnnemyAnimSize.at(EnnemyConfig::BIRD) };
}
