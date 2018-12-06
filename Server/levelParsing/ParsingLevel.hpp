/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include <map>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include "Server/includes/Utils.hpp"
#include "Server/Monsters/includes/IEnnemy.hpp"

namespace Game {
    class ParsingLevel {
    public:
        ParsingLevel();

        void startGame();

        bool isEnd() const noexcept;

        std::vector<Game::MonsterInfo> getMonster(float time);

        int getLevel()const noexcept;

        bool setStreamLevel(int level);

    private:
        bool m_end { false };
        std::string m_levelPath;
        float m_time;

        std::ifstream m_stream;
        bool m_isRunning;
        int m_currentLevel;
        std::multimap<float, Game::MonsterInfo> m_monsters;
    };
}