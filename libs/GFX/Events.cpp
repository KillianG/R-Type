//
// Created by killian on 13/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include <SFML/Window/Event.hpp>
#include "Events.hpp"
#include <iostream>

/**
 * simple constructor
 * @param mgr eventmanager
 */
gfx::Event::Event(EventManager &mgr) : _mgr(mgr){
}

/**
 * get all events using sfml poll event
 * @param window the window where the events come from
 */
void gfx::Event::getEvents(std::shared_ptr<sf::RenderWindow> window) {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed)
            this->_mgr.emit<gfx::ClickEvent>(std::forward<gfx::Vector2I>({event.mouseButton.x, event.mouseButton.y}));
        if (event.type == sf::Event::MouseButtonReleased)
            this->_mgr.emit<gfx::MouseReleaseEvent>(
                    std::forward<gfx::Vector2I>({event.mouseButton.x, event.mouseButton.y}));
        if (event.type == sf::Event::MouseMoved)
            this->_mgr.emit<gfx::MouseMoveEvent>(std::forward<gfx::Vector2I>({event.mouseMove.x, event.mouseMove.y}));
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space)
                this->_mgr.emit<gfx::KeyPressedEvent>(std::forward<std::string>("Space"));
            if (event.key.code == sf::Keyboard::Escape)
                this->_mgr.emit<gfx::KeyPressedEvent>(std::forward<std::string>("Escape"));
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space)
                this->_mgr.emit<gfx::KeyReleasedEvent>(std::forward<std::string>("Space"));
        }
        if (event.type == sf::Event::TextEntered) {
            std::string str = "";
            sf::Utf32::encodeAnsi(event.text.unicode, std::back_inserter(str), 'e');
            this->_mgr.emit<gfx::InputEvent>(std::forward<std::string>(str));
        }
    }
}

/**
 * simple constructor for clickevent
 * @param pos the position
 */
gfx::ClickEvent::ClickEvent(gfx::Vector2I pos) : pos(pos) {}

/**
 * getter for position of clickevent
 * @return
 */
const gfx::Vector2I gfx::ClickEvent::getPosition() const {
    return this->pos;
}

const gfx::Vector2I gfx::MouseMoveEvent::getPosition() const {
    return this->pos;
}

gfx::MouseMoveEvent::MouseMoveEvent(gfx::Vector2I pos) : pos(pos) {}

gfx::MouseReleaseEvent::MouseReleaseEvent(gfx::Vector2I pos) : pos(pos) {

}

const gfx::Vector2I gfx::MouseReleaseEvent::getPosition() const {
    return this->pos;
}


gfx::KeyPressedEvent::KeyPressedEvent(std::string key) {
    this->key = key;
}

const std::string &gfx::KeyPressedEvent::getKey() const {
    return this->key;
}

gfx::KeyReleasedEvent::KeyReleasedEvent(std::string key) {
    this->key = key;
}

const std::string &gfx::KeyReleasedEvent::getKey() const {
    return this->key;
}

std::string gfx::InputEvent::input = "";

gfx::InputEvent::InputEvent(std::string input) {
    gfx::InputEvent::input += input;
}

std::string gfx::InputEvent::clear() {
    std::string copy = gfx::InputEvent::input;
    gfx::InputEvent::input.clear();
    return copy;
}

