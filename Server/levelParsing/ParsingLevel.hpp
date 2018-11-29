/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#ifndef R_TYPE_PARSINGLEVEL_HPP
#define R_TYPE_PARSINGLEVEL_HPP

#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include "Server/includes/Utils.hpp"
#include "Server/Monsters/includes/IEnnemy.hpp"

namespace Game {
    struct MonsterInfo {
    public:
        MonsterInfo() :
                _type(""), _pos{0, 0}, _timer(0), _endGame(false) {}

        MonsterInfo(std::string type, float x, float y, float setTimer) :
                _type(type), _pos{x, y}, _timer(setTimer), _endGame(false) {}

        MonsterInfo(std::string type, Game::vector2f sPos, float setTimer) :
                _type(type), _pos(sPos), _timer(setTimer), _endGame(false) {}

        friend std::istream &operator>>(std::istream &is, MonsterInfo &mInfo) {
            is >> mInfo._type;
            is >> mInfo._pos.x;
            is >> mInfo._pos.y;
            is >> mInfo._timer;
            return is;
        }

    public:
        std::string _type;
        Game::vector2f _pos;
        float _timer;
        bool _endGame;
    };

    class ParsingLevel {
    public:
        ParsingLevel();

        ~ParsingLevel();

        void startGame();

        std::vector<Game::MonsterInfo> getMonster(float time);

    private:
        void setStreamLevel(int level);

        std::string m_levelPath;
        float m_time;

        std::ifstream m_stream;
        bool m_isRunning;
        int m_currentLevel;
        Game::MonsterInfo m_currentMonster;
        Game::MonsterInfo m_currentMonster2;
    };


}


#endif //R_TYPE_PARSINGLEVEL_HPP
