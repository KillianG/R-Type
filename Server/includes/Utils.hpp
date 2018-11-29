//
// Created by nhyarlathotep on 19/11/18.
//

#pragma once

#include <chrono>
#include <cstdint>
#include "../../libs/Exception/Exception.hpp"

namespace Game {

    enum class MovementDir {
        left,
        right,
        up,
        down,
        none
    };

    enum class Team {
        ally,
        ennemy,
        none
    };

    struct box {
        int width { 0 };
        int height { 0 };
    };

    class vector2f {
    public:
        float x { 0 };
        float y { 0 };

        void translate(float toX = 0, float toY = 0) {
            x += toX;
            y += toY;
        }
    };
}

namespace rtype {

        class RfcException : public rtype::Exception
        {
        public:
        	explicit RfcException(std::string error): Exception(error) {}
        };

}
