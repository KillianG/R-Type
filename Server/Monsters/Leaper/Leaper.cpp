//
// Created by nhyarlathotep on 25/11/18.
//

#include "Leaper.hpp"

Leaper::Leaper(EnnemyConfig::EnnemySpriteId id, int hp) : AEnnemy(id, hp) {}

MovableHitBox Leaper::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    _dir.y = (_pos.y >= 720.0f / 2) ? _dir.y : -_dir.y;
    return AEnnemy::init(pos);
}

std::vector<Game::ShootEvent> Leaper::shootMissiles() {
    return std::vector<Game::ShootEvent>();
}

std::vector<Game::MonsterInfo> Leaper::spawnEnnemies() {
    return std::vector<Game::MonsterInfo>();
}

const Game::vector2f &Leaper::update(float timeSinceLastFrame) noexcept {
    if (_pos.x <= 0 || _pos.x >= 1280 - EnnemyConfig::EnnemyHitboxes.at(_spriteId).width) {
        _dir.x = -_dir.x;
    } else if (_pos.y <= 0 || _pos.y >= 720 - EnnemyConfig::EnnemyHitboxes.at(_spriteId).height)
        _dir.y = -_dir.y;
    _pos.translate(-_dir.x * timeSinceLastFrame, -_dir.y * timeSinceLastFrame);
    return _pos;
}
