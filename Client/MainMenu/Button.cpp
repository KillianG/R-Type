#include <utility>

//
// Created by prat on 12/11/18.
//

#include "Button.hpp"
#include "TextManager.hpp"
#include "libs/LOG/Logger.hpp"
#include "algorithm"

/**
 * Button constructor
 * @param window The window where the button will be displayed
 * @param buttonPath The path of the asset
 * @param buttonName The button's name
 * @param onPress The onPress function
 * @param onRelease The onRelease function
 * @param onHover The onHover function
 */
Button::Button(std::shared_ptr<gfx::Window> &&window, const std::string &buttonPath, const std::string &buttonName, std::function<void()> &&onPress, std::function<void()> &&onRelease, std::function<void()> &&onHover)
: onPress(onPress), onRelease(onRelease), onHover(onHover), window(window), name(buttonName), toDraw(true) {
    window->addSprite(buttonPath, buttonName);
}

/**
 * Function that set the button position
 * @param pos position
 */
void Button::setPosition(gfx::Vector2Float pos) {
    this->window->getSpriteByName(name)->setPosition(pos);
}

/**
 * Callback press function
 * Function that will be called when the button is pressed
 */
void Button::callbackPressed() {
    this->onPress();
    auto textManager = this->getWindow()->getTextManager();

    this->setPosition({this->getPosition().x + 4, this->getPosition().y + 4});
    textManager->setPosition(this->getTextName(), {textManager->getPosition(this->getTextName()).x + 4, textManager->getPosition(this->getTextName()).y + 4});
}

/**
 * Callback release function
 * Function that will be called when the button is release
 */
void Button::callbackRelease() {
    this->onRelease();
    auto textManager = this->getWindow()->getTextManager();

    this->setPosition({this->getPosition().x - 4, this->getPosition().y - 4});
    textManager->setPosition(this->getTextName(), {textManager->getPosition(this->getTextName()).x - 4, textManager->getPosition(this->getTextName()).y - 4});
}

/**
 * Callback hover function
 * Function that will be called when the button is hovered in
 */
void Button::callbackHover() {
    this->onHover();
}

/**
 * Window getter
 * @return Window
 */
std::shared_ptr<gfx::Window> Button::getWindow() {
    return this->window;
}

/**
 * Button name getter
 * @return Button name
 */
const std::string &Button::getName() const {
    return this->name;
}

/**
 * Set text function
 * @param text message displayed
 * @param size of text
 * @param color of text
 */
void Button::setText(const std::string &text, unsigned int size, const std::string &color) {
    this->textName = text;
    this->window->getTextManager()->addText("manaspc", size, text, text);
    this->window->getTextManager()->setPosition(text, {this->window->getSpriteByName(this->name)->getPosition().x, this->window->getSpriteByName(this->name)->getPosition().y});
    this->window->getTextManager()->setPosition(text, {this->window->getSpriteByName(this->name)->getPosition().x, this->window->getSpriteByName(this->name)->getPosition().y});
}

/**
 * Function that sets the center of the button
 * @param pos Positions
 */
void Button::setCenter(gfx::Vector2Float pos) {
    this->window->getSpriteByName(this->name)->setCenter(pos);
}

/**
 * Position getter
 * @return The position
 */
const gfx::Vector2Float &Button::getPosition() const {
    return std::forward<gfx::Vector2Float>({this->window->getSpriteByName(this->name)->getPosition().x, this->window->getSpriteByName(this->name)->getPosition().y});
}

/**
 * Text name getter
 * @return the text name
 */
const std::string &Button::getTextName() const {
    return this->textName;
}

/**
 * Function that set the RGBA of the text
 * @param R
 * @param G
 * @param B
 * @param A
 */
void Button::setColorText(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
    this->color.insert({{"R", R}, {"G", G}, {"B", B}, {"A", A}});
    this->window->getTextManager()->setColor(this->getTextName(), R, G, B, A);
}

void Button::setToDraw(bool b) {
    this->window->getSpriteByName(this->name)->setToDraw(b);
    if (!b)
        this->window->getTextManager()->setColor(this->textName, this->color.find("R")->second, this->color.find("G")->second, this->color.find("B")->second, 0);
    else
        this->window->getTextManager()->setColor(this->textName, this->color.find("R")->second, this->color.find("G")->second, this->color.find("B")->second, this->color.find("A")->second);
    this->toDraw = b;
}

bool Button::getToDraw() {
    return this->toDraw;
}

void Button::setOnPress(std::function<void()> onPress) {
    this->onPress = std::move(onPress);
}

void Button::setOnReLease(std::function<void()> onReLease) {
    this->onRelease = std::move(onReLease);
}

void Button::setOnHover(std::function<void()> onHover) {
    this->onHover = std::move(onHover);
}

void Button::setPosText(gfx::Vector2Float pos) {
    this->window->getTextManager()->setPosition(this->textName, pos);
}

void Button::setScale(gfx::Vector2Float scale) {
    this->window->getSpriteByName(this->name)->setScale(scale);
}

std::unordered_map<std::string, uint8_t> Button::getColorText() {
    return this->color;
}
