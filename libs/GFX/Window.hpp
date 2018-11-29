//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef R_TYPE_WINDOW_HPP
#define R_TYPE_WINDOW_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <utility>
#include "GfxManager.hpp"
#include "Sprite.hpp"
#include "TextManager.hpp"
#include "Events.hpp"
#include "Mouse.hpp"

namespace gfx {
    class Event;
};

namespace gfx {
    class Window {
    public:

        friend class gfx::Mouse;

        Window(std::string title, gfx::Vector2Int pos, EventManager &evtManager);
        Window(std::string title, gfx::Vector2Int pos);

        ~Window() = default;

        void closeWindow();
        void clearWindow(sf::Color color);
        void clearWindow();
        void setVisible(bool visible);
        void addSprite(std::string path, std::string name);
        void run();
        std::shared_ptr<gfx::Sprite> getSpriteByName(std::string name);
        gfx::Vector2Int getSize();
        std::shared_ptr<gfx::TextManager> getTextManager();
        void removeSprite(std::string name);
        void clearAll();
    private:
        std::shared_ptr<sf::RenderWindow> getWindow();
        std::shared_ptr<gfx::TextManager> textManager;
        sf::Color color;
        std::shared_ptr<gfx::Event> events;
        std::shared_ptr<sf::RenderWindow> window;
        std::vector<std::shared_ptr<gfx::Sprite>> sprites;
    };
}

#else

namespace gfx {
    class Window;
};

#endif //R_TYPE_WINDOW_HPP
