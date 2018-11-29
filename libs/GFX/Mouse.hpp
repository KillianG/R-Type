//
// Created by killian on 05/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef R_TYPE_MOUSE_HPP
#define R_TYPE_MOUSE_HPP

#include <SFML/Window.hpp>
#include <unordered_map>
#include "GfxManager.hpp"

namespace gfx {
    class Mouse {
    public:
        enum Button {
            LEFT,
            RIGHT,
            MIDDLE
        };
        Mouse();
        ~Mouse() = default;

        const gfx::Vector2Int getPosition() const;
        const gfx::Vector2Int getPosition(gfx::Window window) const;

        bool isButtonPressed(gfx::Mouse::Button button) const;

        void setPosition(gfx::Vector2Int pos);
        void setPosition(gfx::Vector2Int pos, gfx::Window window);
    private:
        std::unordered_map<gfx::Mouse::Button, sf::Mouse::Button> buttons;
    };
}

#else

namespace gfx {
    class Mouse;
};


#endif //R_TYPE_MOUSE_HPP
