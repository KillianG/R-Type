//
// Created by killian on 12/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef RTYPE_LIBS_TEXT_HPP
#define RTYPE_LIBS_TEXT_HPP


#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GfxManager.hpp"
#include "Window.hpp"

namespace gfx {
    class TextManager {
    public:
        friend class gfx::Window;

        TextManager() = default;
        ~TextManager() = default;

        void loadFont(std::string name, std::string path);
        void addText(std::string font, unsigned int size, std::string text, std::string name);
        void setPosition(std::string name, gfx::Vector2Float pos);
        void setSize(std::string name, unsigned int size);
        void setRotation(std::string name, float degree);
        void setColor(std::string name, std::string color);
        void setColor(std::string name, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        gfx::Vector2Float getSize(std::string name);
        void setCenter(std::string name, gfx::Vector2Float pos);
        const gfx::Vector2Float &getPosition(std::string name) const;
        void setScale(std::string name, float x, float y);
        void setText(std::string name, std::string text);
        void clearAll();

    private:
        void draw(std::shared_ptr<sf::RenderWindow> window);
        std::unordered_map<std::string, sf::Text> texts;
        std::unordered_map<std::string, sf::Font> fonts;

    };
}


#else

namespace gfx {
    class TextManager;
};


#endif //RTYPE_LIBS_TEXT_HPP
