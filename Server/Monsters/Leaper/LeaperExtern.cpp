//
// Created by nhyarlathotep on 05/12/18.
//

#include "Leaper.hpp"

extern "C" {
    std::string getName() {return "Leaper";}
    IEnnemy::Ptr getMonsterLibrary() { return std::make_unique<Leaper>(); }
};