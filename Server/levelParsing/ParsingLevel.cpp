/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/11 by ebernard
*/

#include "ParsingLevel.hpp"

Game::ParsingLevel::ParsingLevel() : m_levelPath("./assets/Levels/"), m_isRunning(false), m_currentLevel(-1) {
}

void Game::ParsingLevel::startGame() {
    m_isRunning = true;
    if (!setStreamLevel(1))
        rtype::Exception("No level config for level 1");
}

std::vector<Game::MonsterInfo> Game::ParsingLevel::getMonster(float time) {
    std::vector<Game::MonsterInfo> monsterList{};

    if (!m_isRunning)
        throw rtype::Exception("startGame never called");

    m_time += time;

    for (auto it = m_monsters.begin(); it != m_monsters.lower_bound(m_time);) {
        monsterList.push_back(std::move(it->second));
        it = m_monsters.erase(it);
    }
    if (m_monsters.empty())
        m_end = true;
    return monsterList;
}

bool Game::ParsingLevel::setStreamLevel(int level) {
    std::string line;

    m_time = 0;
    m_currentLevel = level;
    m_stream = std::ifstream(m_levelPath + "level" + std::to_string(level) + ".config");
    if (!m_stream.is_open()) {
        m_stream = std::ifstream("../assets/Levels/level" + std::to_string(level) + ".config");
    }
    if (!m_stream.is_open())
        return false;
    std::getline(m_stream, line);
    Game::MonsterInfo m_currentMonster;

    m_stream >> m_currentMonster;
    while (!m_currentMonster._endGame) {
        m_monsters.emplace(m_currentMonster._timer, m_currentMonster);
        m_stream >> m_currentMonster;
    }
    m_end = false;
    m_currentMonster._endGame = false;
    return m_stream.is_open();
}

int Game::ParsingLevel::getLevel() const noexcept {
    return m_currentLevel;
}

bool Game::ParsingLevel::isEnd() const noexcept {
    return m_end;
}
