//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "GfxManager.hpp"
#include "Window.hpp"
#include "../LOG/Logger.hpp"
#include "../Exception/Exception.hpp"

const std::map<std::string, sf::Color> gfx::Manager::colors = std::map<std::string, sf::Color>({
                                         {"red", sf::Color::Red},
                                         {"green", sf::Color::Green},
                                         {"blue", sf::Color::Blue},
                                         {"white", sf::Color::White},
                                         {"yellow", sf::Color::Yellow},
                                         {"black", sf::Color::Black},
                                         {"tranparent", sf::Color::Transparent}
                                 });

/**
 * Function that stop displaying old window and push new window to the window's stack
 * Multithread safe with mutex
 * @param name Name of the window you want to create
 * @param dimensions Dimensions of the window you want to create (width, height)
 */
void gfx::Manager::new_window(std::string name, gfx::Vector2Int pos, EventManager &evtManager) {
    m_mutex.lock();
    Logger::log(Logger::LogType::info, "Creating window: " + name);
    if (!this->windows.empty())
        this->windows.top()->setVisible(false);
    this->windows.push(std::shared_ptr<gfx::Window>(new gfx::Window(name, pos, evtManager)));
    Logger::log(Logger::LogType::info, "Window created");
    m_mutex.unlock();
}

/**
 * Function that close the current open window and get back to the old one
 * Multithread safe with mutex
 */
void gfx::Manager::close_window() {
    m_mutex.lock();
    Logger::log(Logger::LogType::info, "Closing current window" );
    if (this->windows.top()) {
        this->windows.top()->closeWindow();
        Logger::log(Logger::LogType::info, "Window closed");
        this->windows.pop();
        if (!this->windows.empty())
            this->windows.top()->setVisible(true);
    } else {
        Logger::log(Logger::LogType::warn, "Can't close window");
    }
    m_mutex.unlock();
}

/**
 * Function that gives you the current openned window
 * @return The current displayed window
 */
std::shared_ptr<gfx::Window> gfx::Manager::getWindow() {
    if (windows.empty())
        return nullptr;
    return windows.top();
}

/***
 * Change the background of the window
 * Multithread safe with mutex
 * @param color Color of the background {red, green, blue, white, yellow, black or transparent}
 */
void gfx::Manager::setBackgroundColor(std::string color) {
    m_mutex.lock();
    auto it = gfx::Manager::colors.find(color);
    if (it != gfx::Manager::colors.end()) {
        this->windows.top()->clearWindow(it->second);
        Logger::log(Logger::LogType::info, "Window cleared");
    } else {
        m_mutex.unlock();
        throw rtype::Exception("Color not found: " + color);
    }
    m_mutex.unlock();
}

/**
 * Constructor, inits the colors map
 */
gfx::Manager::Manager() {
    Logger::log(Logger::LogType::info, "Creating gfx manager");
    this->mouse = std::shared_ptr<gfx::Mouse>(new gfx::Mouse());
    Logger::log(Logger::LogType::info, "Gfx manager created");
}

/**
 * Multithread safe with mutex
 * Function to run everytime
 */
void gfx::Manager::run() {
    this->windows.top()->run();
}

/**
 * simple getter for windows
 * @return window's stack
 */
const std::stack<std::shared_ptr<gfx::Window>> &gfx::Manager::getWindows() const {
    return this->windows;
}

/**
 * getter of keyboardManager
 * @return keyboardManager
 */
const gfx::KeyboardManager &gfx::Manager::getKeyboardManager() const {
    return this->keyboardManager;
}

/**
 * Simple getter for the mouse
 * @return the mouse
 */
std::shared_ptr<gfx::Mouse> gfx::Manager::getMouse() const {
    return this->mouse;
}

/**
 * getter for soundmanager
 * @return sound manager
 */
gfx::SoundManager &gfx::Manager::getSoundManager() {
    return this->soundManager;
}

/**
 * another new window without eventmanager
 * @param name name of the window
 * @param size size of the window
 */
void gfx::Manager::new_window(std::string name, gfx::Vector2Int size) {
    m_mutex.lock();
    Logger::log(Logger::LogType::info, "Creating window: " + name);
    if (!this->windows.empty())
        this->windows.top()->setVisible(false);
    this->windows.push(std::shared_ptr<gfx::Window>(new gfx::Window(name, size)));
    Logger::log(Logger::LogType::info, "Window created");
    m_mutex.unlock();
}

