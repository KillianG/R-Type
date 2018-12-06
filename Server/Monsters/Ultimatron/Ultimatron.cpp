//
// Created by nhyarlathotep on 25/11/18.
//

#include <random>
#include "Ultimatron.hpp"

extern "C" {
    std::string getName() {return "Ultimatron";}
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Ultimatron>(); }
};

Ultimatron::Ultimatron() : AEnnemy(EnnemyConfig::ULTIMATRON, 250) {}

MovableHitBox Ultimatron::initEnnemy(const Game::vector2f &pos) noexcept {
    _pos = pos;
    return AEnnemy::init(pos);
}

bool Ultimatron::shootMissile() noexcept {
    if (_isShooting && _timeSinceLastFrame >= _coolDownTime) {
        _timeSinceLastFrame = 0;
        return true;
    }
    return false;
};

std::vector<Game::ShootEvent> Ultimatron::partern1() {
    std::vector<Game::ShootEvent> shoot {};

    _coolDownTime = 0.1;
    static constexpr Game::vector2f start { 120, 240 };
    static constexpr Game::vector2f limits { 174, 186 };
    static Game::vector2f angles { start.x, start.y };

    if (angles.x >= limits.x || angles.y <= limits.y) {
        static float time { 0 };
        time += _coolDownTime;
        if (time >= 2.0) {
            time = 0;
            angles = start;
            _isShooting = false;
            return shoot;
        }
    } else {
        angles.x += 2.5;
        angles.y -= 2.5;
    }
    shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(angles.x, _speedMissile * 2));
    shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(angles.y, _speedMissile * 2));
    return shoot;
}

std::vector<Game::ShootEvent> Ultimatron::partern2() {
    std::vector<Game::ShootEvent> shoot{};

    _coolDownTime = 0.08;
    static bool _phase { true };
    static constexpr Game::vector2f limits { 120, 240 };
    static float _currentAngle { limits.x };

    shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(_currentAngle, _speedMissile));
    if (_currentAngle >= limits.y) {
        _phase = false;
        _currentAngle = limits.y - 3;
    } else if (_currentAngle <= limits.x && !_phase) {
        _phase = true;
        _isShooting = false;
        _currentAngle = limits.x;
    }
    _currentAngle += (_phase) ? 8 : -8;
    return shoot;
}

std::vector<Game::ShootEvent> Ultimatron::partern3() {
    std::vector<Game::ShootEvent> shoot {};

    static float time { 0 };
    _coolDownTime = 2;
    time += _coolDownTime;
    if (time > 10) {
        time = 0;
        _isShooting = false;
        return shoot;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(160, 200);
    int spacePos = dis(gen);

    for (float currentAngle = 120.0f; currentAngle < 240; ) {
        shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(currentAngle, _speedMissile));
        currentAngle += (currentAngle <= spacePos && currentAngle + 2.5 >= spacePos) ? 10 : 2.5;
    }
    return shoot;
}

std::vector<Game::ShootEvent> Ultimatron::shootMissiles() {
    if (_choice == 1) {
        return partern1();
    } else if (_choice == 2) {
        return partern2();
    } else if (_choice == 3)
        return partern3();
    return partern1();
}

std::vector<Game::MonsterInfo> Ultimatron::spawnEnnemies() {
    return std::vector<Game::MonsterInfo>();
}

const Game::vector2f &Ultimatron::update(float timeSinceLastFrame) noexcept {
    if (!_isShooting)
        _time += timeSinceLastFrame;
    if (_time > _BurstcoolDownTime && !_isShooting) {
        /* Shoots every 6 seconds */
        _time = 0;
        _choice += 1;
        if (_choice > 3)
            _choice = 1;
        _isShooting = true;
    }
    _timeSinceLastFrame += timeSinceLastFrame;

    if (_pos.x > 1280 - EnnemyConfig::EnnemyHitboxes.at(_spriteId).width) {
        _pos.translate(-40 * timeSinceLastFrame, 0);
    }
    return _pos;
}