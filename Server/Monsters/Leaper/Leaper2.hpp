//
// Created by nhyarlathotep on 04/12/18.
//

#pragma once

#include "Leaper.hpp"

class Leaper2 : public Leaper {
public:
    Leaper2();

    std::vector<Game::ShootEvent> shootMissilesOnDeath() override;

private:
    static constexpr float _speedMissile { 450 };
};