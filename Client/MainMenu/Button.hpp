//
// Created by prat on 12/11/18.
//

#ifndef R_TYPE_BUTTON_HPP
#define R_TYPE_BUTTON_HPP


#include <libs/GFX/GfxManager.hpp>
#include "libs/EventManager/Receiver.hpp"
#include "libs/EventManager/EventManager.hpp"

/**
 * Button class
 * Every button class must inherit from this class
 */
class Button {
public:
    Button(std::shared_ptr<gfx::Window> &&window, const std::string &buttonPath, const std::string &buttonName, std::function<void()> &&onPress, std::function<void()> &&onRelease, std::function<void()> &&onHover);
    ~Button() = default;

    void setPosition(gfx::Vector2Float pos);
    void setCenter(gfx::Vector2Float pos);
    const gfx::Vector2Float &getPosition() const;
    virtual void callbackPressed();
    virtual void callbackRelease();
    virtual void callbackHover();
    std::shared_ptr<gfx::Window> getWindow();
    const std::string &getName() const;
    virtual void setText(const std::string &text, unsigned int size, const std::string &color);
    const std::string &getTextName() const;
    void setColorText(uint8_t R, uint8_t G, uint8_t B, uint8_t A);
    std::unordered_map<std::string, uint8_t> getColorText();
    void setToDraw(bool b);
    bool getToDraw();
    void setScale(gfx::Vector2Float scale);
    void setPosText(gfx::Vector2Float pos);
    void setOnPress(std::function<void()> onPress);
    void setOnReLease(std::function<void()> onReLease);
    void setOnHover(std::function<void()> onHover);

    std::function<void()> onPress;
    std::function<void()> onRelease;
    std::function<void()> onHover;

protected:
    std::unordered_map<std::string, uint8_t> color;
    std::string textName;
    std::shared_ptr<gfx::Window> window;
    const std::string name;
    bool toDraw;
};


#endif //R_TYPE_BUTTON_HPP
