//
// Created by nhyarlathotep on 25/11/18.
//

#include "FirsBoss.hpp"

extern "C" {
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<FirstBoss>(); }
    std::string getName() { return "FirstBoss"; }
};

FirstBoss::FirstBoss() : AEnnemy(EnnemyConfig::FIRSTBOSS, 100) {}

MovableHitBox FirstBoss::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    return AEnnemy::init(pos);
}

std::vector<Game::ShootEvent> FirstBoss::shootMissiles() {
    std::vector<Game::ShootEvent> shoot{};

    for (auto i = _angles.x; i < _angles.y;) {
        shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(i, _speedMissile));
        i += 13;
    }
    _isShooting = false;
    return shoot;
}

std::vector<Game::MonsterInfo> FirstBoss::spawnEnnemies() {
    return { std::vector<Game::MonsterInfo>() };
}

const Game::vector2f &FirstBoss::update(float timeSinceLastFrame) noexcept {
    if (_pos.x <= 600 || _pos.x >= 1280 - EnnemyConfig::EnnemyHitboxes.at(_spriteId).width) {
        _dir.x = -_dir.x;
    } else if (_pos.y <= 0 || _pos.y >= 720 - EnnemyConfig::EnnemyHitboxes.at(_spriteId).height)
        _dir.y = -_dir.y;
    _pos.translate(-_dir.x * timeSinceLastFrame, -_dir.y * timeSinceLastFrame);

    if (!_isShooting)
        _time += timeSinceLastFrame;
    if (_time > _burstcoolDownTime && !_isShooting) {
        _time = 0;
        _isShooting = true;
    }
    return _pos;
}