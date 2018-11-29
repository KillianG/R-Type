//
// Created by killian on 12/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "TextManager.hpp"
#include "../LOG/Logger.hpp"
#include "../Exception/Exception.hpp"

/**
 * @brief load a font for texts with name
 * @param name name of the font
 * @param path path to the font file
 */
void gfx::TextManager::loadFont(std::string name, std::string path) {
    if (this->fonts.find(name) != this->fonts.end())
        throw rtype::Exception("Font with this name " + name + " already exists");
    this->fonts.insert(std::pair<std::string, sf::Font>(name.c_str(), *ResourceManager::get().loadFont(path) ));
}

/**
 * adding a text to the textManager
 * @param font name of the font (added with loadFont())
 * @param size the size of the characters
 * @param text the text
 * @param name the name of the text
 */
void gfx::TextManager::addText(std::string font, unsigned int size, std::string text, std::string name) {
    if (this->fonts.find(font) == this->fonts.end())
        throw rtype::Exception("No font with the name: " + font);
    Logger::log(Logger::LogType::info, "Adding text: " + name);
    texts.insert(std::make_pair<std::string, sf::Text>(name.c_str(), sf::Text(text, this->fonts.find(font)->second, size)));
}

/**
 * draw the texts
 * @param window the window in which you want the text to be displayed
 */
void gfx::TextManager::draw(std::shared_ptr<sf::RenderWindow> window) {
    for (auto &&txt : this->texts) {
        window->draw(txt.second);
    }
}

/**
 * set the position of a text
 * @param name name of the text
 * @param pos the position
 */
void gfx::TextManager::setPosition(std::string name, gfx::Vector2Float pos) {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);
    it->second.setPosition(pos.x, pos.y);
}

/**
 * set the size of a text
 * @param name name of the text
 * @param size size wanted
 */
void gfx::TextManager::setSize(std::string name, unsigned int size) {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);
    it->second.setCharacterSize(size);
}

/**
 * rotate the text
 * @param name name of the text
 * @param degree degree of rotation
 */
void gfx::TextManager::setRotation(std::string name, float degree) {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);
    it->second.setRotation(degree);
}

void gfx::TextManager::setColor(std::string name, std::string color) {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);

    for (auto &&col : gfx::Manager::colors) {
        if (col.first == color) {
            it->second.setFillColor(col.second);
            it->second.setOutlineColor(col.second);
        }
    }
}

/**
 * set center of the text
 * @param name name of the text
 * @param pos position of the text
 */
void gfx::TextManager::setCenter(std::string name, gfx::Vector2Float pos) {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);
    it->second.setOrigin(pos.x, pos.y);
}

/**
 * Change the color of the text using rgba
 * @param name name of the text
 * @param r red
 * @param g green
 * @param b blue
 * @param a alpha
 */
void gfx::TextManager::setColor(std::string name, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);
    sf::Color color = {r, g, b, a};
    it->second.setFillColor(color);
    it->second.setOutlineColor(color);
}

/**
 * get the size of a text
 * @param name name of the text
 * @return the size of the text x = width, y = height
 */
gfx::Vector2Float gfx::TextManager::getSize(std::string name) {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);
    auto bounds = it->second.getGlobalBounds();
    auto width = bounds.width;
    auto height = bounds.height;
    return {width, height};
}

/**
 * getter for position of text
 * @param name name of the text
 * @return the position
 */
const gfx::Vector2Float &gfx::TextManager::getPosition(std::string name) const {
    auto it = this->texts.find(name);
    if (it == this->texts.end())
        throw rtype::Exception("Cannot find text with the name: " + name);
    return std::forward<gfx::Vector2Float>({it->second.getPosition().x, it->second.getPosition().y});
}

void gfx::TextManager::clearAll() {
    this->texts.clear();
}

/**
 * set scale of text
 * @param name name of the text
 * @param x x factor (lol)
 * @param y y factor
 */
void gfx::TextManager::setScale(std::string name, float x, float y) {
    auto it = this->texts.find(name);
    if (it != this->texts.end())
        it->second.setScale(x, y);
}

void gfx::TextManager::setText(std::string name, std::string text) {
    auto it = this->texts.find(name);
    if (it != this->texts.end())
        it->second.setString(text);
}
