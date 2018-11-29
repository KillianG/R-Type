//
// Created by killian on 13/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef RTYPE_LIBS_EVENTS_HPP
#define RTYPE_LIBS_EVENTS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "../EventManager/BaseEvent.hpp"
#include "../EventManager/EventManager.hpp"



namespace gfx {

    struct Vector2I {
        int x;
        int y;
    };

    class ClickEvent : public BaseEvent {
    public:
        ClickEvent(gfx::Vector2I pos);
        const gfx::Vector2I getPosition() const;
    private:
        gfx::Vector2I pos;
    };

    class KeyReleasedEvent : public BaseEvent {
    public:
        KeyReleasedEvent(std::string key);

        const std::string &getKey() const;

    private:
        std::string key;
    };

    class KeyPressedEvent : public BaseEvent {
    public:
        KeyPressedEvent(std::string key);

        const std::string &getKey() const;

    private:
        std::string key;
    };

    class InputEvent : public BaseEvent {
    public:
        InputEvent(std::string input);
        static std::string input;
        static std::string clear();
    };

    class MouseMoveEvent : public BaseEvent {
    public:
        MouseMoveEvent(gfx::Vector2I pos);
        const gfx::Vector2I getPosition() const;
    private:
        gfx::Vector2I pos;
    };

    class MouseReleaseEvent : public BaseEvent {
    public:
        MouseReleaseEvent(gfx::Vector2I pos);
        const gfx::Vector2I getPosition() const;
    private:
        gfx::Vector2I pos;
    };

    class Event {
    public:
        Event(EventManager &mgr);
        void getEvents(std::shared_ptr<sf::RenderWindow> window);
        void setEventManager(EventManager &mgr);

    private:
        EventManager &_mgr;
    };
}

#else

namespace gfx {
    class ClickEvent;
    class Event;
}

#endif //RTYPE_LIBS_EVENTS_HPP
