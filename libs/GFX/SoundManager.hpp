//
// Created by killian on 05/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef R_TYPE_SOUNDMANAGER_HPP
#define R_TYPE_SOUNDMANAGER_HPP

#include <map>
#include <SFML/Audio/Music.hpp>
#include <memory>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>


namespace gfx {
    class SoundManager {
    public:
        SoundManager() = default;
        ~SoundManager() = default;

        void addMusic(std::string name, std::string musicName);
        void playMusic(std::string name);
        void stopMusic(std::string name);
        void pauseMusic(std::string name);
        void setPlayingOffsetMusic(std::string name, float seconds);
        void setLoopMusic(std::string name, bool loop);
        void setVolumeMusic(std::string name, float volume);
        void setVolume(float vol);

    private:
        float volume { 50 };
        std::map<std::string, std::shared_ptr<sf::Music>> musics;
    };
}


#else

namespace gfx{
    class SoundManager;
};


#endif //R_TYPE_SOUNDMANAGER_HPP
