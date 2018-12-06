//
// Created by nhyarlathotep on 25/11/18.
//

#include "Bird.hpp"

extern "C" {
    std::string getName() {return "Bird";}
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Bird>(); }
};

Bird::Bird() : AEnnemy(EnnemyConfig::BIRD) {}

MovableHitBox Bird::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    _basePosY = pos.y;
    _phase = _pos.y >= 720.0f / 2;
    return AEnnemy::init(pos);
}

std::vector<Game::ShootEvent> Bird::shootMissiles() {
    return { std::vector<Game::ShootEvent>() };
}

std::vector<Game::MonsterInfo> Bird::spawnEnnemies() {
    return std::vector<Game::MonsterInfo>();
}

const Game::vector2f &Bird::update(float timeSinceLastFrame) noexcept {
    if (_phase) {
        _pos.translate(-_dir.x * timeSinceLastFrame, -_dir.y * timeSinceLastFrame);
        if (_pos.y < _basePosY - 100) {
            _phase = false;
        }
    } else {
        _pos.translate(-_dir.x * timeSinceLastFrame, _dir.y * timeSinceLastFrame);
        if (_pos.y > _basePosY + 100) {
            _phase = true;
        }
    }
    return _pos;
}