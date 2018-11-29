/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "ParsingLevel.hpp"

Game::ParsingLevel::ParsingLevel() :
        m_levelPath("assets/Levels/"),
        m_isRunning(false),
        m_currentLevel(1) {
    m_currentMonster._timer = -1.0f;
}

Game::ParsingLevel::~ParsingLevel() {

}

void Game::ParsingLevel::startGame() {
    m_isRunning = true;
    setStreamLevel(1);
    m_time = 0;
    m_stream >> m_currentMonster;
    m_stream >> m_currentMonster2;
}

std::vector<Game::MonsterInfo> Game::ParsingLevel::getMonster(float time) {
    std::vector<Game::MonsterInfo> monsterList{};

    if (!m_isRunning)
        throw rtype::Exception("startGame never called");

    m_time += time;
    while (m_currentMonster._timer <= m_time && !m_currentMonster._endGame) {
        monsterList.push_back(m_currentMonster);
        m_currentMonster = m_currentMonster2;
        m_stream >> m_currentMonster2;
        if (m_stream.eof()) {
            m_currentMonster2._endGame = true;
        }
    }
    return monsterList;
}

void Game::ParsingLevel::setStreamLevel(int level) {
    m_stream = std::ifstream(m_levelPath + "level" + std::to_string(level) + ".config");
    if (!m_stream.is_open())
        m_stream = std::ifstream("../assets/Levels/level" + std::to_string(level) + ".config");
}
