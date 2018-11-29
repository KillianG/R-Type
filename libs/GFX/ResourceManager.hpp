#include <utility>

//
// Created by nhyarlathotep on 14/11/18.
//

#pragma once

#include <memory>
#include <iostream>
#include <type_traits>
#include <unordered_map>
#include <experimental/filesystem>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../LOG/Logger.hpp"
#include "Singleton.hpp"

namespace fs = std::experimental::filesystem;

template<typename Resource>
class ResourceHolder{
public:
    explicit ResourceHolder() noexcept = default;

    template<typename ...Args>
    std::shared_ptr<Resource> openFromFile(const std::string &id, Args &&...args)  {
        auto res = new Resource();

        if (!res->openFromFile(std::forward<Args>(args)...)) {
            throw std::runtime_error("Impossible to loadFromFile file");
        }
        _resources.emplace(id, std::shared_ptr<Resource>(res));
        return get(id);
    }

    template<typename ...Args>
    std::shared_ptr<Resource> loadFromFile(const std::string &id, Args &&...args)  {
        auto res = new Resource();

        if (!res->loadFromFile(std::forward<Args>(args)...)) {
            throw std::runtime_error("Impossible to loadFromFile file");
        }
        _resources.emplace(id, std::shared_ptr<Resource>(res));
        return get(id);
    }

    std::shared_ptr<Resource> get(const std::string &id) {
        return _resources.at(id);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> _resources;
};

class ResourceManager : public gfx::Singleton<ResourceManager> {
    friend class gfx::Singleton<ResourceManager>;
public:

    std::shared_ptr<sf::Font> loadFont(fs::path &&filename);
    std::shared_ptr<sf::Music> loadMusic(fs::path &&filename);
    std::shared_ptr<sf::Texture> loadTexture(fs::path &&filename);

    std::shared_ptr<sf::Font> getFont(const std::string &id);
    std::shared_ptr<sf::Music> getMusic(const std::string &id);
    std::shared_ptr<sf::Texture> getTexture(const std::string &id);

private:
    /**
     * @brief Set the root assets path
     */
    explicit ResourceManager(fs::path &&resourceDirectoryPath = (fs::current_path() / "assets")) noexcept: _resourceDirectoryPath(std::move(resourceDirectoryPath)) {

#ifdef __linux__ 
        Logger::log(Logger::LogType::info, _resourceDirectoryPath);
#endif
    };

    ResourceManager(const ResourceManager &rMgr){};

    fs::path _resourceDirectoryPath;

    ResourceHolder<sf::Font> _fontRegistry;
    ResourceHolder<sf::Music> _musicRegistry;
    ResourceHolder<sf::Texture> _textureRegistry;
};
