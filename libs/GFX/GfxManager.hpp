//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef R_TYPE_GFXMANAGER_HPP
#define R_TYPE_GFXMANAGER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <mutex>
#include <map>
#include "Window.hpp"
#include "Singleton.hpp"
#include "KeyboardManager.hpp"
#include "Mouse.hpp"
#include "SoundManager.hpp"
#include "TextManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "ResourceManager.hpp"

namespace gfx {

    struct Vector2Int {
        int x;
        int y;
    };

    struct Vector2Float {
        float x;
        float y;
    };


class Manager : public gfx::Singleton<gfx::Manager> {
    friend class Singleton<gfx::Manager>;
    public:
        ~Manager() = default;

        void run();

        void new_window(std::string name, gfx::Vector2Int, EventManager &evtManager);
        void new_window(std::string name, gfx::Vector2Int size);
        void close_window();

        void setBackgroundColor(std::string color);

        std::shared_ptr<gfx::Window> getWindow();
        const std::stack<std::shared_ptr<gfx::Window>> &getWindows() const;

        const gfx::KeyboardManager &getKeyboardManager() const;
        const gfx::SoundManager &getSoundManager() const;

        std::shared_ptr<gfx::Mouse> getMouse() const;

        static const std::map<std::string, sf::Color> colors;

    private:
        Manager(const Manager &manager) {};
        Manager();

        gfx::KeyboardManager keyboardManager;
        gfx::SoundManager soundManager;
        std::stack<std::shared_ptr<gfx::Window>> windows;
        std::shared_ptr<gfx::Mouse> mouse;
    };
}
#else
namespace gfx {
    struct Vector2Int;
    struct Vector2Float;
    class Manager;
};

#endif //R_TYPE_GFXMANAGER_HPP
