//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include <iostream>
#include "Window.hpp"

/**
 * Constructor of window
 * @param title Name of the Winfow
 * @param pos Size of the window
 */
gfx::Window::Window(std::string title, gfx::Vector2Int pos, EventManager &evtManager) : events(std::make_shared<gfx::Event>(Event(evtManager))) {
    window = std::shared_ptr<sf::RenderWindow>(
            new sf::RenderWindow(sf::VideoMode(pos.x, pos.y), title, sf::Style::Titlebar | sf::Style::Close));
    window->setFramerateLimit(60);
    window->setPosition({50, 50});
    textManager = std::shared_ptr<gfx::TextManager>(new gfx::TextManager());
}

/**
 * Close this window
 */
void gfx::Window::closeWindow() {
    this->window->close();
}

/**
 * Clear window with the color
 * Change the current background color with the param color
 * @param color the color you want to fill the window
 */
void gfx::Window::clearWindow(sf::Color color) {
    this->color = color;
    this->window->clear(color);
}

/**
 * set if window is visible or not
 * @param visible boolean true for visible false for invisible
 */
void gfx::Window::setVisible(bool visible) {
    this->window->setVisible(visible);
}

/**
 * create a new sprite and add it to the vector sprites
 * @param path path to the image (absolute or relative)
 * @param name name of the sprite, important, you will use it later to get your sprite
 */
void gfx::Window::addSprite(std::string path, std::string name) {
    this->sprites.push_back(std::shared_ptr<gfx::Sprite>(new gfx::Sprite(path, name)));
}

/**
 * function that must be called everytime, this draws the sprites in the window and display the window
 */
void gfx::Window::run() {
    for (auto &&sprite : sprites) {
        if (sprite->getToDraw())
            this->window->draw(sprite->getSprite());
    }
    this->textManager->draw(this->window);
    if (this->events != nullptr)
        this->events->getEvents(this->window);
    this->window->display();
    this->clearWindow();
}

/**
 * Get a sprite by his name
 * @param name name of the sprite given in addSprite
 * @return returns the sprite of throw and error
 */
std::shared_ptr<gfx::Sprite> gfx::Window::getSpriteByName(std::string name) {
    for (auto &&sprite : sprites) {
        if (!sprite->getName().compare(name)) {
            return sprite;
        }
    }
    return nullptr;
}

/**
 * window getter
 * @return the window
 */
std::shared_ptr<sf::RenderWindow> gfx::Window::getWindow() {
    return this->window;
}

/**
 * Simple getter for the window size
 * @return the window size
 */
gfx::Vector2Int gfx::Window::getSize() {
    return {static_cast<int>(this->window->getSize().x), static_cast<int>(this->window->getSize().y)};
}

/**
 * Clear the window with the current background color
 */
void gfx::Window::clearWindow() {
    this->window->clear(this->color);
}

void gfx::Window::clearAll() {
    this->sprites.clear();
    this->textManager->clearAll();
}

/**
 * Constructor for window without eventmanager
 * @param title title of the window
 * @param pos the size of the window
 */
gfx::Window::Window(std::string title, gfx::Vector2Int pos) : events(nullptr) {
    window = std::shared_ptr<sf::RenderWindow>(
            new sf::RenderWindow(sf::VideoMode(pos.x, pos.y), title, sf::Style::Titlebar | sf::Style::Close));
    window->setFramerateLimit(60);
    textManager = std::shared_ptr<gfx::TextManager>(new gfx::TextManager());
}

/**
 * getter for textmanager
 * @return the textmanager
 */
std::shared_ptr<gfx::TextManager> gfx::Window::getTextManager() {
    return this->textManager;
}

/**
 * remove a sprite
 * @param name the name of the sprite
 */
void gfx::Window::removeSprite(std::string name) {
    for (auto it = sprites.begin(); it != sprites.end(); it++) {
        if ((*it)->getName() == name) {
            sprites.erase(it);
            break;
        }
    }
}
