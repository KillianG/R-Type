//
// Created by prat on 22/11/18.
//

#ifndef R_TYPE_MENUBUTTON_HPP
#define R_TYPE_MENUBUTTON_HPP

#include "Button.hpp"
#include <libs/GFX/GfxManager.hpp>

/**
 * MenuButton Class
 * Inherits from the Button Class
 */
class MenuButton : public Button {
public:
    MenuButton(std::shared_ptr<gfx::Window> &&window, const std::string &buttonPath, const std::string &buttonName, std::function<void()> &&onPress, std::function<void()> &&onRelease, std::function<void()> &&onHover);
    ~MenuButton() = default;
    virtual void callbackPressed();
    virtual void callbackRelease();
    virtual void callbackHover();
private:
    void setText(const std::string &text, unsigned int size, const std::string &color);
};


#endif //R_TYPE_MENUBUTTON_HPP
