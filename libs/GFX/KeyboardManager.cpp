//
// Created by killian on 01/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "KeyboardManager.hpp"
#include "../LOG/Logger.hpp"

/**
 * Function that initialise unsorted map of KeyName and Key
 * Used letter to encapsulate SFML keyboard utilization
 */
void gfx::KeyboardManager::initKeyMap() {
    Logger::log(Logger::LogType::info, "Initializing KeyMap");
#define INSERT_KEY(identifier) this->keyMap.insert(std::make_pair(#identifier, sf::Keyboard::identifier));

    INSERT_KEY(Unknown);
    INSERT_KEY(A);
    INSERT_KEY(B);
    INSERT_KEY(C);
    INSERT_KEY(D);
    INSERT_KEY(E);
    INSERT_KEY(F);
    INSERT_KEY(G);
    INSERT_KEY(H);
    INSERT_KEY(I);
    INSERT_KEY(J);
    INSERT_KEY(K);
    INSERT_KEY(L);
    INSERT_KEY(M);
    INSERT_KEY(N);
    INSERT_KEY(O);
    INSERT_KEY(P);
    INSERT_KEY(Q);
    INSERT_KEY(R);
    INSERT_KEY(S);
    INSERT_KEY(T);
    INSERT_KEY(U);
    INSERT_KEY(V);
    INSERT_KEY(W);
    INSERT_KEY(X);
    INSERT_KEY(Y);
    INSERT_KEY(Z);
    INSERT_KEY(Num0);
    INSERT_KEY(Num1);
    INSERT_KEY(Num2);
    INSERT_KEY(Num3);
    INSERT_KEY(Num4);
    INSERT_KEY(Num5);
    INSERT_KEY(Num6);
    INSERT_KEY(Num7);
    INSERT_KEY(Num8);
    INSERT_KEY(Num9);
    INSERT_KEY(Escape);
    INSERT_KEY(LControl);
    INSERT_KEY(LShift);
    INSERT_KEY(LAlt);
    INSERT_KEY(LSystem);
    INSERT_KEY(RControl);
    INSERT_KEY(RShift);
    INSERT_KEY(RAlt);
    INSERT_KEY(RSystem);
    INSERT_KEY(Menu);
    INSERT_KEY(LBracket);
    INSERT_KEY(RBracket);
    INSERT_KEY(SemiColon);
    INSERT_KEY(Comma);
    INSERT_KEY(Period);
    INSERT_KEY(Quote);
    INSERT_KEY(Slash);
    INSERT_KEY(BackSlash);
    INSERT_KEY(Tilde);
    INSERT_KEY(Equal);
    INSERT_KEY(Dash);
    INSERT_KEY(Space);
    INSERT_KEY(Return);
    INSERT_KEY(BackSpace);
    INSERT_KEY(Tab);
    INSERT_KEY(PageUp);
    INSERT_KEY(PageDown);
    INSERT_KEY(End);
    INSERT_KEY(Home);
    INSERT_KEY(Insert);
    INSERT_KEY(Delete);
    INSERT_KEY(Add);
    INSERT_KEY(Subtract);
    INSERT_KEY(Multiply);
    INSERT_KEY(Divide);
    INSERT_KEY(Left);
    INSERT_KEY(Right);
    INSERT_KEY(Up);
    INSERT_KEY(Down);
    INSERT_KEY(Numpad0);
    INSERT_KEY(Numpad1);
    INSERT_KEY(Numpad2);
    INSERT_KEY(Numpad3);
    INSERT_KEY(Numpad4);
    INSERT_KEY(Numpad5);
    INSERT_KEY(Numpad6);
    INSERT_KEY(Numpad7);
    INSERT_KEY(Numpad8);
    INSERT_KEY(Numpad9);
    INSERT_KEY(F1);
    INSERT_KEY(F2);
    INSERT_KEY(F3);
    INSERT_KEY(F4);
    INSERT_KEY(F5);
    INSERT_KEY(F6);
    INSERT_KEY(F7);
    INSERT_KEY(F8);
    INSERT_KEY(F9);
    INSERT_KEY(F10);
    INSERT_KEY(F11);
    INSERT_KEY(F12);
    INSERT_KEY(F13);
    INSERT_KEY(F14);
    INSERT_KEY(F15);
    INSERT_KEY(Pause);

#undef INSERT_KEY
    Logger::log(Logger::LogType::info, "KeyMap initialized");
}

/**
 * Constructor that call initKeyMap
 */
gfx::KeyboardManager::KeyboardManager() {
    this->initKeyMap();
}

/**
 * Function that return an sf::Keyboard::Key from its name
 * @param name Name of the Key, for example "Space" "Escape" "A"...
 * @return The key corresponding to the name passed as parameters, Unknown if key is not in my map
 */
sf::Keyboard::Key gfx::KeyboardManager::getKeyByName(std::string name) const {
    auto it = keyMap.find(name);
    if (it == keyMap.end()) {
        Logger::log(Logger::LogType::warn, "Key " + name + " not found");
        return sf::Keyboard::Unknown;
    }
    return it->second;
}

/**
 * Returns true if key is pressed and false if not
 * @param name Name of the key you want to know if it's pressed or not
 * @return Boolean
 */
bool gfx::KeyboardManager::isKeyPressed(std::string name) {
    return (sf::Keyboard::isKeyPressed(this->getKeyByName(name)));
}
