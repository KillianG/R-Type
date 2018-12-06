//
// Created by nhyarlathotep on 05/12/18.
//

#include "Leaper2.hpp"

extern "C" {
    std::string getName() {return "Leaper2";}
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Leaper2>(); }
};

Leaper2::Leaper2() : Leaper(EnnemyConfig::LEAPER2, 5) {
    _isShootingOnDeath = true;
}

std::vector<Game::ShootEvent> Leaper2::shootMissilesOnDeath() {
    std::vector<Game::ShootEvent> shoot;

    for (auto i = 0u; i < 360; i += 20)
        shoot.emplace_back(0, Game::Team::ennemy, 0, Game::vector2f::DegreeToVec(i, _speedMissile));
    return shoot;
}
