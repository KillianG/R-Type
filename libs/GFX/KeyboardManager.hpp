//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef R_TYPE_KEYBOARDMANAGER_HPP
#define R_TYPE_KEYBOARDMANAGER_HPP

#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

namespace gfx {
    class KeyboardManager {
    public:
        KeyboardManager();
        ~KeyboardManager() = default;
        bool isKeyPressed(std::string name);
    private:
        void initKeyMap();
        std::unordered_map<std::string, sf::Keyboard::Key> keyMap;
        sf::Keyboard::Key getKeyByName(std::string name) const;
    };
}


#else

namespace gfx {
    class KeyBoardManager;
}


#endif //R_TYPE_KEYBOARDMANAGER_HPP
