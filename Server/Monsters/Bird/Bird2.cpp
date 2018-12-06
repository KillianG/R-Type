//
// Created by nhyarlathotep on 25/11/18.
//

#include <random>
#include "Bird2.hpp"

extern "C" {
std::string getName() {return "Bird2";}
IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Bird2>(); }
};

Bird2::Bird2() : AEnnemy(EnnemyConfig::BIRD2), _time(10) , _shootStart(std::chrono::system_clock::now()){}

MovableHitBox Bird2::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    _basePosY = pos.y;
    _isShooting = true;
    _phase = _pos.y >= 720.0f / 2;
    return AEnnemy::init(pos);
}

std::vector<Game::ShootEvent> Bird2::shootMissiles() {
    std::vector<Game::ShootEvent> shoot{};
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 10);

    if (std::chrono::duration_cast<std::chrono::duration<float, std::deci>>(std::chrono::system_clock::now() - _shootStart).count() > _time) {
    	auto up = _phase ? 1 : -1;
    	Game::vector2f move{-450, static_cast<float>(-450 * up) * 0.5f * static_cast<float>(dis(gen) * 0.1)};
    	_time = std::chrono::duration_cast<std::chrono::duration<float, std::deci>>(std::chrono::system_clock::now() - _shootStart).count() + 10;
        shoot.emplace_back(0, Game::Team::ennemy, 0, std::forward<Game::vector2f>(move));
    }
    return shoot;
}

std::vector<Game::MonsterInfo> Bird2::spawnEnnemies() {
    return std::vector<Game::MonsterInfo>();
}

const Game::vector2f &Bird2::update(float timeSinceLastFrame) noexcept {
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
