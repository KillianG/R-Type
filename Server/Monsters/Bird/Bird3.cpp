//
// Created by nhyarlathotep on 25/11/18.
//

#include <random>
#include "Bird3.hpp"

extern "C" {
std::string getName() {return "Bird3";}
IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Bird3>(); }
};

Bird3::Bird3() : AEnnemy(EnnemyConfig::BIRD3, 4) {}

MovableHitBox Bird3::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    _isShooting = true;
    return AEnnemy::init(pos);
}

bool Bird3::shootMissile() noexcept {
    if (_isShooting && _timeSinceLastFrame >= _coolDownTime) {
        _timeSinceLastFrame = 0;
        return true;
    }
    return false;
}

std::vector<Game::ShootEvent> Bird3::shootMissiles() {
    std::vector<Game::ShootEvent> shoot{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-55, 55);

    shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(dis(gen), _speedMissile));
    return shoot;
}

std::vector<Game::MonsterInfo> Bird3::spawnEnnemies() {
    return std::vector<Game::MonsterInfo>();
}

const Game::vector2f &Bird3::update(float timeSinceLastFrame) noexcept {
    _timeSinceLastFrame += timeSinceLastFrame;
    _pos.translate(-_dir.x * timeSinceLastFrame, -_dir.y * timeSinceLastFrame);
    return _pos;
}
