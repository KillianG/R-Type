//
// Created by killian on 05/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include "Mouse.hpp"
#include "../LOG/Logger.hpp"
#include "../Exception/Exception.hpp"

/**
 * Simple constructor of Mouse
 * Initialize Buttons map
 */
gfx::Mouse::Mouse() {
    Logger::log(Logger::LogType::info, "Initializing mouse manager");
    this->buttons = {
            {gfx::Mouse::Button::LEFT, sf::Mouse::Left},
            {gfx::Mouse::Button::RIGHT, sf::Mouse::Right},
            {gfx::Mouse::Button::MIDDLE, sf::Mouse::Middle},
    };
    Logger::log(Logger::LogType::info, "Mouse manager initialized");
}

/**
 * get the position of the mouse on the desktop
 * @return the position of the mouse relative to the desktop
 */
const gfx::Vector2Int gfx::Mouse::getPosition() const {
    return {sf::Mouse::getPosition().x, sf::Mouse::getPosition().y};
}

/**
 * return boolean if a mouse button is pressed
 * @param button the button you want to check
 * @return boolean true if button is pressed false if not
 */
bool gfx::Mouse::isButtonPressed(gfx::Mouse::Button button) const {
    auto it = buttons.find(button);
    if (it == buttons.end()) {
        throw rtype::Exception("This mouse button does not exist");
    }
    return (sf::Mouse::isButtonPressed(it->second));
}

/**
 * Set the position of the mouse on the desktop
 * @param pos the position
 */
void gfx::Mouse::setPosition(gfx::Vector2Int pos) {
    Logger::log(Logger::LogType::info, "Changing mouse position");
    sf::Mouse::setPosition({pos.x, pos.y});
    Logger::log(Logger::LogType::info, "Mouse position changed");
}

/**
 * set the position of the mouse relative to the window
 * @param pos the position
 * @param window the window
 */
void gfx::Mouse::setPosition(gfx::Vector2Int pos, gfx::Window window) {
    Logger::log(Logger::LogType::info, "Changing mouse position");
    sf::Mouse::setPosition({pos.x, pos.y}, *window.getWindow());
    Logger::log(Logger::LogType::info, "Mouse position changed");
}

/**
 * get the position of the mouse relative to the window
 * @param window the window
 * @return position of the mouse
 */
const gfx::Vector2Int gfx::Mouse::getPosition(gfx::Window window) const {
    return {sf::Mouse::getPosition(*window.getWindow()).x, sf::Mouse::getPosition(*window.getWindow()).y};
}
