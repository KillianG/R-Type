//
// Created by nhyarlathotep on 25/11/18.
//

#include "Shooter.hpp"

extern "C" {
std::string getName() {return "Shooter";}
IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Shooter>(); }
};

Shooter::Shooter() : AEnnemy(EnnemyConfig::SHOOTER) {}

MovableHitBox Shooter::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    _isShooting = true;
    _dir.y = (_pos.y >= 720.0f / 2) ? _dir.y : -_dir.y;
    return AEnnemy::init(pos);
}

bool Shooter::shootMissile() noexcept {
    if (_isShooting && _timeSinceLastFrame >= _coolDownTime) {
        _timeSinceLastFrame = 0;
        return true;
    }
    return false;
}

std::vector<Game::ShootEvent> Shooter::shootMissiles() {
    std::vector<Game::ShootEvent> shoot{};
    shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(180, _speedMissile));
    return shoot;
}

std::vector<Game::MonsterInfo> Shooter::spawnEnnemies() {
    return std::vector<Game::MonsterInfo>();
}

const Game::vector2f &Shooter::update(float timeSinceLastFrame) noexcept {
    _timeSinceLastFrame += timeSinceLastFrame;
    _pos.translate(-_dir.x * timeSinceLastFrame, -_dir.y * timeSinceLastFrame);
    if (_pos.y <= 0 || _pos.y >= 720 - EnnemyConfig::EnnemyHitboxes.at(_spriteId).height)
        _dir.y = -_dir.y;
    return _pos;
}
