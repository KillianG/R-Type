//
// Created by NANAA on 12/11/18.
//

#ifndef R_TYPE_OPTIONSMENU_HPP
#define R_TYPE_OPTIONSMENU_HPP

#include <Client/MainMenu/Settings.hpp>
#include "libs/EventManager/Receiver.hpp"
#include <unordered_map>
#include <Client/MainMenu/Button.hpp>

class OptionsMenu : public Receiver<OptionsMenu>
{
public:
	OptionsMenu();
	~OptionsMenu() = default;
	void show();
	void hide();



private:
	std::shared_ptr<Button> getButtonByName(const std::string &name);
	void setButtons();
	std::shared_ptr<gfx::Window> _window;
	gfx::Manager &_manager = gfx::Singleton<gfx::Manager>::get();
	std::unordered_map<std::string, std::shared_ptr<Button>> _buttons;

};

#endif //R_TYPE_OPTIONSMENU_HPP
