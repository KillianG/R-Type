//
// Created by killian on 05/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include <iostream>
#include <SFML/Audio/SoundBuffer.hpp>
#include "SoundManager.hpp"
#include "../LOG/Logger.hpp"
#include "../Exception/Exception.hpp"
#include "ResourceManager.hpp"

/**
 * play a music with the name
 * @param name name
 */
void gfx::SoundManager::playMusic(std::string name) {
    auto it = this->musics.find(name);
    if (it == this->musics.end())
        throw rtype::Exception("Error no music loaded with this name: " + name);
    Logger::log(Logger::LogType::info, "Playing music");
    it->second->play();
}

/**
 * stop a music with the name
 * @param name name
 */
void gfx::SoundManager::stopMusic(std::string name) {
    auto it = this->musics.find(name);
    if (it == this->musics.end())
        throw rtype::Exception("Error no music loaded with this name: " + name);
    Logger::log(Logger::LogType::info, "Stopping music");
    it->second->stop();
}

/**
 * pause a music with the name
 * @param name name
 */
void gfx::SoundManager::pauseMusic(std::string name) {
    auto it = this->musics.find(name);
    if (it == this->musics.end())
        throw rtype::Exception("Error no music loaded with this name: " + name);
    Logger::log(Logger::LogType::info, "Pausing music");
    it->second->pause();
}

/**
 * set playing offset of the music
 * @param name name
 * @param seconds number of seconds to offset
 */
void gfx::SoundManager::setPlayingOffsetMusic(std::string name, float seconds) {
    auto it = this->musics.find(name);
    if (it == this->musics.end())
        throw rtype::Exception("Error no music loaded with this name: " + name);
    Logger::log(Logger::LogType::info, "Setting playing offset music");
    it->second->setPlayingOffset(sf::seconds(seconds));
}

/**
 * set a music to loop or not
 * @param name name
 * @param loop tru for looping false for not
 */
void gfx::SoundManager::setLoopMusic(std::string name, bool loop) {
    auto it = this->musics.find(name);
    if (it == this->musics.end())
        throw rtype::Exception("Error no music loaded with this name: " + name);
    Logger::log(Logger::LogType::info, "Set loop music");
    it->second->setLoop(loop);
}

/**
 * change the volume of a music
 * @param name name
 * @param volume the volume
 */
void gfx::SoundManager::setVolumeMusic(std::string name, float volume) {
    auto it = this->musics.find(name);
    if (it == this->musics.end())
        throw rtype::Exception("Error no music loaded with this name: " + name);
    Logger::log(Logger::LogType::info, "Changing music volume");
    it->second->setVolume(volume);
}

/**
 * add a music to the map
 * @param name name of the music
 * @param musicName path to the music file (no .mp3)
 */
void gfx::SoundManager::addMusic(std::string name, std::string musicName) {
    Logger::log(Logger::LogType::info, "Adding music");
    auto it = musics.find(name);
    if (it != musics.end()) {
        Logger::log(Logger::LogType::warn, "Music already exists");
        throw rtype::Exception("Error while loading music: " + name);
    }
    this->musics.insert(std::make_pair<std::string, std::shared_ptr<sf::Music>>(std::string(name),
                                                                                ResourceManager::get().loadMusic(musicName)));
    it = this->musics.find(name);
    if (it == this->musics.end())
        throw rtype::Exception("Error no music loaded with this name: " + name);
    it->second->setVolume(this->volume);
    Logger::log(Logger::LogType::info, "New music added to map");
}

void gfx::SoundManager::setVolume(float vol) {
    this->volume = vol;
    for (auto &&music : this->musics) {
        music.second->setVolume(vol);
    }
}
