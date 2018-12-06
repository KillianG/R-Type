//
// Created by nhyarlathotep on 14/11/18.
//

#include <utility>
#include "ResourceManager.hpp"

/**
 * @brief it will load the requested sf::Music
 * @param filename [in] the music's filename without the path && extension
 * @return the loaded sf::Music
 */
std::shared_ptr<sf::Music> ResourceManager::loadMusic(fs::path &&filename) {
    for (auto &it :fs::recursive_directory_iterator(_resourceDirectoryPath)) {
        if (it.status().type() !=fs::file_type::directory) {
            if (it.path().filename().stem() == filename) {
                return _musicRegistry.openFromFile(std::move(it.path().stem()), it.path());
            }
        }
    }
    return _musicRegistry.openFromFile(std::move(filename.stem()), filename);
}

/**
 * @brief it will load the requested sf::Texture
 * @param filename [in] the texture's filename without the path && extension
 * @return the loaded sf::Texture
 */
std::shared_ptr<sf::Texture> ResourceManager::loadTexture(fs::path &&filename) {
    for (auto &it :fs::recursive_directory_iterator(_resourceDirectoryPath)) {
        if (it.status().type() !=fs::file_type::directory) {
            if (it.path().filename().stem() == filename) {
                return _textureRegistry.loadFromFile(std::move(it.path().stem()), it.path());
            }
        }
    }
    return _textureRegistry.loadFromFile(std::move(filename.stem()), filename);
}

/**
 * @brief it will load the requested sf::Font
 * @param filename [in] the font's filename without the path && extension
 * @return the loaded sf::Font
 */
std::shared_ptr<sf::Font> ResourceManager::loadFont(fs::path &&filename) {
    for (auto &it :fs::recursive_directory_iterator(_resourceDirectoryPath)) {
        if (it.status().type() !=fs::file_type::directory) {
            if (it.path().filename().stem() == filename) {
                return _fontRegistry.loadFromFile(std::move(it.path().stem()), it.path());
            }
        }
    }
    return _fontRegistry.loadFromFile(std::move(filename.stem()), filename);
}

/**
 * @brief it will get the requested sf::Music
 * @param filename [in] the music's filename without the path && extension
 * @return the loaded sf::Music
 */
std::shared_ptr<sf::Music> ResourceManager::getMusic(const std::string &id) {
    return _musicRegistry.get(id);
}

/**
 * @brief it will get the requested sf::Music
 * @param filename [in] the music's filename without the path && extension
 * @return the loaded sf::Music
 */
std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string &id) {
    return _textureRegistry.get(id);
}

/**
 * @brief it will get the requested sf::Music
 * @param filename [in] the music's filename without the path && extension
 * @return the loaded sf::Music
 */
std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string &id) {
    return _fontRegistry.get(id);
}

ResourceManager::ResourceManager(fs::path &&resourceDirectoryPath) noexcept: _resourceDirectoryPath(std::move(resourceDirectoryPath)) {

#ifdef __linux__
    Logger::log(Logger::LogType::info, _resourceDirectoryPath);
#endif
};
