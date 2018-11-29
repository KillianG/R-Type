//
// Created by prat on 22/11/18.
//

#include "MenuButton.hpp"
#include "../../libs/GFX/Window.hpp"

/**
 * Menu Button constructor
 * Call the Button constructor
 * @param window The window where the button will be displayed
 * @param buttonPath The path of the asset
 * @param buttonName The button's name
 * @param onPress The onPress function
 * @param onRelease The onRelease function
 * @param onHover The onHover function
 */
MenuButton::MenuButton(std::shared_ptr<gfx::Window> &&window, const std::string &buttonPath, const std::string &buttonName, std::function<void()> &&onPress, std::function<void()> &&onRelease, std::function<void()> &&onHover)
: Button(std::move(window), buttonPath, buttonName, std::move(onPress), std::move(onRelease), std::move(onHover)) {
}

/**
 * Set text function
 * Set the wanted position
 * @param text message displayed
 * @param size of text
 * @param color of text
 */
void MenuButton::setText(const std::string &text, unsigned int size, const std::string &color) {
    Button::setText(text, size, color);
    this->window->getTextManager()->setCenter(text, {this->window->getTextManager()->getSize(text).x + 20, -6});
}

/**
 * Add a short animation when pressed
 */
void MenuButton::callbackPressed() {
    auto textManager = this->getWindow()->getTextManager();

    this->setPosition({this->getPosition().x - 4, this->getPosition().y + 4});
    textManager->setPosition(this->getTextName(), {textManager->getPosition(this->getTextName()).x - 4, textManager->getPosition(this->getTextName()).y + 4});
}

/**
 * Add a short animation when released
 */
void MenuButton::callbackRelease() {
    this->onRelease();
    auto textManager = this->getWindow()->getTextManager();

    this->setPosition({this->getPosition().x + 4, this->getPosition().y - 4});
    textManager->setPosition(this->getTextName(), {textManager->getPosition(this->getTextName()).x + 4, textManager->getPosition(this->getTextName()).y - 4});
}

/**
 * Change the color when hovered
 */
void MenuButton::callbackHover() {
    this->setColorText(204, 102, 0, 255);
}
