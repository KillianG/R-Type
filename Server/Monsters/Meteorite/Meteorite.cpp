//
// Created by nhyarlathotep on 25/11/18.
//

#include "Meteorite.hpp"

extern "C" {
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Meteorite>(); }
    std::string getName() { return "Meteorite"; }
};

Meteorite::Meteorite() : AEnnemy(EnnemyConfig::METEORITE) {}

MovableHitBox Meteorite::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    _indestructible = true;
    return { EnnemyConfig::EnnemyHitboxes.at(_spriteId), pos, _spriteId, EnnemyConfig::EnnemyAnimSize.at(_spriteId), 0.08f };
}

std::vector<Game::ShootEvent> Meteorite::shootMissiles() {
    return std::vector<Game::ShootEvent>();
}

std::vector<Game::MonsterInfo> Meteorite::spawnEnnemies() {
    return std::vector<Game::MonsterInfo>();
}

const Game::vector2f &Meteorite::update(float timeSinceLastFrame) noexcept {
    _pos.translate(_dir.x * timeSinceLastFrame, 0);
    return _pos;
}