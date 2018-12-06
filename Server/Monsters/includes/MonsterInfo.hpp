//
// Created by nhyarlathotep on 30/11/18.
//

#pragma once

#include <string>
#include "../../includes/Utils.hpp"

namespace Game {
    struct MonsterInfo {
    public:
        MonsterInfo() :
                _type(""), _pos{0, 0}, _timer(0), _endGame(false) {}

        MonsterInfo(std::string &&type, float x, float y, float setTimer) :
                _type(type), _pos{x, y}, _timer(setTimer), _endGame(false) {}

        MonsterInfo(std::string &&type, Game::vector2f sPos, float setTimer = 0) :
                _type(type), _pos(sPos), _timer(setTimer), _endGame(false) {}

        friend std::istream &operator>>(std::istream &is, MonsterInfo &mInfo) {
            is >> mInfo._type;
            is >> mInfo._pos.x;
            is >> mInfo._pos.y;
            is >> mInfo._timer;
            mInfo._endGame = is.eof();
            return is;
        }

    public:
        std::string _type;
        Game::vector2f _pos;
        float _timer;
        bool _endGame;
    };
}
