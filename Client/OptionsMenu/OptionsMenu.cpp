//
// Created by NANAA on 12/11/18.
//

#include <Client/MainMenu/MenuButton.hpp>
#include <libs/Exception/Exception.hpp>
#include "OptionsMenu.hpp"

void OptionsMenu::setButtons()
{

	std::cout << "Getting window" << std::endl;
	auto windowSize = _manager.getWindow()->getSize();
	std::cout << "Got window\n";
	auto windowHeight = static_cast<float> (windowSize.x);
	auto windowWidth = static_cast<float> (windowSize.y);

	this->_buttons.insert(std::make_pair<std::string, std::shared_ptr<Button>>("VolumePlus", std::make_shared<Button>(MenuButton(this->_manager.getWindow(), "button1", "VolumePlus", [](){}, [](){}, [](){}))));

	auto volumePlusButton = getButtonByName("VolumePlus");

	volumePlusButton->setPosition({200.0, 200.0});
	volumePlusButton->setText("GROS PD", 25, "white");
	volumePlusButton->setPosText({250.0f, 200.0f});


}

std::shared_ptr<Button> OptionsMenu::getButtonByName(const std::string &name)
{
	auto it = _buttons.find(name);
	if (it == _buttons.end())
		throw rtype::Exception("Can't find button by name: " + name);
	return it->second;
}

OptionsMenu::OptionsMenu()
{
	std::cout << "Options menu ctor\n";
	setButtons();
}

void OptionsMenu::show()
{
	for (auto &button : _buttons)
		button.second.get()->setToDraw(true);

}

void OptionsMenu::hide()
{
	for (auto &button : _buttons)
		button.second.get()->setToDraw(false);
}
