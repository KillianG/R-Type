#include <utility>

//
// Created by prat on 12/11/18.
//

#include "MainMenu.hpp"
#include "Button.hpp"
#include "Splash.hpp"
#include "MenuButton.hpp"
#include "../game/Game.hpp"
#include "../../libs/LOG/Logger.hpp"
#include "../../libs/GFX/Events.hpp"
#include "../../libs/Exception/Exception.hpp"
#include "../../libs/GFX/Sprite.hpp"

/**
 * MainMenu Constructor
 * Subscribe to event manager
 */
MainMenu::MainMenu() : quit(false), drawIp(false),drawJoinPwd(false), drawServerName(false), drawPwd(false), gameNameInputReleased(false), pwdInputReleased(false), selectedGame(""), buttonPressed("") {
    this->_evtMgr.subscribe<gfx::ClickEvent>(*this);
    this->_evtMgr.subscribe<gfx::MouseReleaseEvent>(*this);
    this->_evtMgr.subscribe<gfx::MouseMoveEvent>(*this);
    this->_evtMgr.subscribe<gfx::InputEvent>(*this);
    this->drawIp = false;
    this->createGame = false;
    this->joinPwdGame = false;
}

/**
 * Menu Launcher function
 * Display the menu
 */
void MainMenu::launch() {
    gfx::KeyboardManager kbMan;

    this->manager.new_window("R-Type", {1280, 720}, this->_evtMgr);
    setSprites();
    setButtons();

    while (!kbMan.isKeyPressed("Escape")) {
        animation();
        this->manager.run();
        if (this->createGame) {
            this->createGame = false;
            this->_evtMgr.unsubscribeAll(*this);
            try {
                this->game = std::make_shared<GameBase>(GameBase(this->ipToConnect, 50000, this->_evtMgr, 5455, 5456));
                this->game->createGame(this->gameNameInput, this->pwdInput);
            } catch (...) {
                MainMenu menu;
                menu.launch();
            }
            std::_Exit(0);
        }
        if (this->joinPwdGame) {
            this->joinPwdGame = false;
            this->_evtMgr.unsubscribeAll(*this);
            try {
                GameBase game = GameBase(this->ipToConnect, 50000, this->_evtMgr, 5402, 5401);
                game.joinGame(this->selectedGame, gfx::InputEvent::clear());
            } catch (...) {
                MainMenu menu;
                menu.launch();
            }
            std::_Exit(0);
        }
    }
}


/**
 * Function used when SinglePlayer Button is released
 */
void MainMenu::onReleaseSinglePlayerButton() {
    this->getButtonByName("singlePlayer")->setOnReLease([this](){
        Logger::log(Logger::LogType::info, "SINGLEPLAYER RELEASED");
        this->_evtMgr.unsubscribeAll(*this);
        try {
            GameBase game("127.0.0.1", 50000, this->_evtMgr, 42421, 42422);
            game.createGame("THESECRETNAMEOFTHELOCALGAMEYOUMISTNOTCREATETHESAME", "34567UIJNBVDEZ45678OKJHGFDE5678IOLKJHGFDERTYUIKJHVDSE45678IKJHGCFDXSZSD");
        } catch (...) {
            this->manager.getWindow()->closeWindow();
            MainMenu menu;
            menu.launch();
            std::_Exit(0);
        }
    });
}

/**
 * Function used when MultiPlayer Button is released
 */
void MainMenu::onReleaseMultiPlayerButton() {
    this->getButtonByName("multiPlayer")->setOnReLease([this]() {
        ipInputDisplay(true);
    });
}

/**
 * Function used when Options Button is released
 */
void MainMenu::onReleaseOptionsButton() {
    this->getButtonByName("options")->setOnReLease([this](){

    	showOptionsMenu(true);
	    Logger::log(Logger::LogType::info, "OPTIONS RELEASED");
    });
}

void MainMenu::onReleaseJoinGameButton() {
    this->getButtonByName("joinGame")->setOnReLease([this]() {
        if (!this->selectedGame.empty()) {
            displayServerList(false);
            pwdJoinInputDisplay(true);
        }
    });
}

/**
 * Function used when Quit Button is released
 */
void MainMenu::onReleaseQuitButton() {
    this->getButtonByName("quit")->setOnReLease([this]() {
        this->manager.getWindow()->closeWindow();
        std::_Exit(0);
    });
}

/**
 * Function that sets the sprites and fonts
 */
void MainMenu::setSprites() {
    this->splash.init(this->manager.getWindow(), "minecraft");
    auto window = this->manager.getWindow();

    window->getTextManager()->loadFont("hydrogen", "hydrogen whiskey");
    window->getTextManager()->loadFont("manaspc", "manaspc");

    window->addSprite("background", "background");
    window->addSprite("foggy", "fog");
    window->addSprite("planet", "planet");
    window->addSprite("logo_header", "header");
    window->addSprite("panel", "panel");


    window->getSpriteByName("planet")->setPosition({50, 800});
    window->getSpriteByName("planet")->setScale({1.25, 1.25});
    window->getSpriteByName("planet")->setCenter({320, 320.5});
    window->getSpriteByName("fog")->setPosition({0, -200});
    window->getSpriteByName("fog")->clip({0, 0}, {99999, 99999});
    window->getSpriteByName("panel")->setPosition({455, 150});
    window->getSpriteByName("panel")->setToDraw(false);

    window->getTextManager()->addText("hydrogen", 110, "R  -  T  Y  P  E", "title");
    window->getTextManager()->addText("manaspc", 27, "GAME LIST", "gameList");
    window->getTextManager()->setCenter("title", {window->getTextManager()->getSize("title").x / 2, window->getTextManager()->getSize("title").y / 2});
    window->getTextManager()->setPosition("title", {static_cast<float>(window->getSize().x / 2), 98});
    window->getTextManager()->setColor("gameList", 255, 255, 255, 0);
    window->getTextManager()->setPosition("gameList", {555, 160});
    window->getTextManager()->addText("manaspc", 25, "", "serverip");
    window->getTextManager()->addText("manaspc", 25, "", "serverName");
    window->getTextManager()->addText("manaspc", 25, "", "pwd");
    window->getTextManager()->addText("manaspc", 25, "", "joinPwd");
    window->getTextManager()->addText("manaspc", 25, "", "upKeyInput");
    window->getTextManager()->addText("manaspc", 25, "", "downKeyInput");
    window->getTextManager()->addText("manaspc", 25, "", "leftKeyInput");
    window->getTextManager()->addText("manaspc", 25, "", "rightKeyInput");
    window->getTextManager()->addText("manaspc", 25, "", "shootKeyInput");


	window->getTextManager()->setPosition("serverip", {420, 320});
    window->getTextManager()->setPosition("serverName", {420, 220});
    window->getTextManager()->setPosition("pwd", {420, 320});
    window->getTextManager()->setPosition("joinPwd", {420, 320});
    window->getTextManager()->setPosition("upKeyInput", {360, 190});
	window->getTextManager()->setPosition("downKeyInput", {350, 20});
	window->getTextManager()->setPosition("leftKeyInput", {350, 330});
	window->getTextManager()->setPosition("rightKeyInput", {350, 480});
	window->getTextManager()->setPosition("shootKeyInput", {350, 625});


	this->splash.display();
}

/**
 * Function that sets the buttons map
 */
void MainMenu::setButtons() {
    this->buttons.insert(std::make_pair<std::string, std::shared_ptr<Button>>("singlePlayer", std::make_shared<MenuButton>(MenuButton(this->manager.getWindow(), "button1", "singlePlayer", [](){}, [](){}, [](){}))));
    this->buttons.insert(std::make_pair<std::string, std::shared_ptr<Button>>("multiPlayer", std::make_shared<MenuButton>(MenuButton(this->manager.getWindow(), "button2", "multiPlayer", [](){}, [](){}, [](){}))));
    this->buttons.insert(std::make_pair<std::string, std::shared_ptr<Button>>("options", std::make_shared<MenuButton>(MenuButton(this->manager.getWindow(), "button3", "options", [](){}, [](){}, [](){}))));
    this->buttons.insert(std::make_pair<std::string, std::shared_ptr<Button>>("quit", std::make_shared<MenuButton>(MenuButton(this->manager.getWindow(), "button4", "quit", [](){}, [](){}, [](){}))));

    getButtonByName("singlePlayer")->setCenter({330, 0});
    getButtonByName("multiPlayer")->setCenter({280, 0});
    getButtonByName("options")->setCenter({230, 0});
    getButtonByName("quit")->setCenter({182, 0});

    getButtonByName("singlePlayer")->setPosition({static_cast<float>(this->manager.getWindow()->getSize().x), static_cast<float>(this->manager.getWindow()->getSize().y) - 250});
    getButtonByName("multiPlayer")->setPosition({static_cast<float>(this->manager.getWindow()->getSize().x), static_cast<float>(this->manager.getWindow()->getSize().y) - 200});
    getButtonByName("options")->setPosition({static_cast<float>(this->manager.getWindow()->getSize().x), static_cast<float>(this->manager.getWindow()->getSize().y) - 150});
    getButtonByName("quit")->setPosition({static_cast<float>(this->manager.getWindow()->getSize().x), static_cast<float>(this->manager.getWindow()->getSize().y) - 100});

    getButtonByName("singlePlayer")->setText("SINGLEPLAYER", 25, "white");
    getButtonByName("multiPlayer")->setText("MULTIPLAYER", 25, "white");
    getButtonByName("options")->setText("OPTIONS", 25, "white");
    getButtonByName("quit")->setText("QUIT", 25, "white");

    onReleaseSinglePlayerButton();
    onReleaseMultiPlayerButton();
    onReleaseOptionsButton();
    onReleaseQuitButton();
}

/**
 * Click event function
 * @param event
 */
void MainMenu::receive(gfx::ClickEvent event) {
    for (auto &&button : this->buttons) {
        if (isInBounds(button.second, event.getPosition()) && button.second->getToDraw()) {
            button.second->callbackPressed();
            this->buttonPressed = button.second->getName();
        }
    }
}

/**
 * Mouse release event function
 * @param event
 */
void MainMenu::receive(gfx::MouseReleaseEvent event) {
    if (!this->buttonPressed.empty()) {
        getButtonByName(this->buttonPressed)->callbackRelease();
        this->buttonPressed = "";
    }
    changeKeyBindingsEvent(event);

    if (this->manager.getWindow()->getSpriteByName("inputGameName") != nullptr && this->manager.getWindow()->getSpriteByName("inputGameName")->getToDraw() && isInBoundsSprite("inputGameName", event.getPosition())) {
        this->gameNameInputReleased = true;
        this->pwdInputReleased = false;
        this->drawServerName = true;
        this->drawPwd = false;
        gfx::InputEvent::clear();
    }
    if (this->manager.getWindow()->getSpriteByName("inputPwd") != nullptr && this->manager.getWindow()->getSpriteByName("inputPwd")->getToDraw() && isInBoundsSprite("inputPwd", event.getPosition())) {
        this->gameNameInputReleased = false;
        this->pwdInputReleased = true;
        this->drawPwd = true;
        this->drawServerName = false;
        gfx::InputEvent::clear();
    }
}

/**
 * Mouse move event function
 * @param event
 */
void MainMenu::receive(gfx::MouseMoveEvent event) {
    for (auto &&button : this->buttons) {
        if (isInBounds(button.second, event.getPosition()) && button.second->getToDraw()) {
            button.second->callbackHover();
        }
        else if (!buttonExist("joinGame") || !getButtonByName("joinGame")->getToDraw()) {
            reset(button.second);
        }
    }
}

void MainMenu::receive(gfx::InputEvent event) {
    if (this->drawIp) {
        this->manager.getWindow()->getTextManager()->setText("serverip", gfx::InputEvent::input);
    }
    if (this->drawServerName) {
        this->manager.getWindow()->getTextManager()->setText("serverName", gfx::InputEvent::input);
        this->gameNameInput = gfx::InputEvent::input;
    }
    else if (this->drawPwd) {
        this->manager.getWindow()->getTextManager()->setText("pwd", gfx::InputEvent::input);
        this->pwdInput = gfx::InputEvent::input;
    }
    else if (this->drawJoinPwd) {
        this->manager.getWindow()->getTextManager()->setText("joinPwd", gfx::InputEvent::input);
    }
    else if (this->_upInputReleased)  {
	    manager.getWindow()->getTextManager()->setText("upKeyInput", "");
    	manager.getWindow()->getTextManager()->setText("upKeyInput", gfx::InputEvent::input);
    }
    else if (this->_downInputReleased)  {
	    manager.getWindow()->getTextManager()->setText("downKeyInput", gfx::InputEvent::input);
    }
    else if (this->_leftInputReleased)  {
	    manager.getWindow()->getTextManager()->setText("leftKeyInput", gfx::InputEvent::input);
    }
    else if (this->_rightInputReleased)  {
	    manager.getWindow()->getTextManager()->setText("rightKeyInput", gfx::InputEvent::input);
    }
    else if (this->_shootInputRelased)  {
	    manager.getWindow()->getTextManager()->setText("shootKeyInput", gfx::InputEvent::input);
    }

}

/**
 * Function that checks if the coordinates are in the bounds of the button
 * @param button
 * @param pos coordinates
 * @return true if pos is in bounds, else false
 */
bool MainMenu::isInBounds(std::shared_ptr<Button> button, gfx::Vector2I pos) {
    auto rect = button->getWindow()->getSpriteByName(button->getName())->getBounds();
    return pos.x >= rect.left && pos.x <= rect.right && pos.y <= rect.down && pos.y >= rect.up;
}

bool MainMenu::isInBoundsSprite(std::string spriteName, gfx::Vector2I pos) {
    auto rect = this->manager.getWindow()->getSpriteByName(std::move(spriteName))->getBounds();
    return pos.x >= rect.left && pos.x <= rect.right && pos.y <= rect.down && pos.y >= rect.up;
}

/**
 * Function that gets a button given a name
 * @param name of the button
 * @return button object
 */
std::shared_ptr<Button> MainMenu::getButtonByName(const std::string &name) {
    auto it = this->buttons.find(name);
    if (it == this->buttons.end())
        throw rtype::Exception("Can't find button by name: " + name);
    return it->second;
}

/**
 * Animation of sprites function
 */
void MainMenu::animation() {
    this->manager.getWindow()->getSpriteByName("fog")->move(gfx::direction::LEFT, 0.08);
    this->manager.getWindow()->getSpriteByName("planet")->rotate(0.016);
    this->splash.animation(0.8, 1.3);
}

/**
 * Reset the color of the given button
 * @param button
 */
void MainMenu::reset(std::shared_ptr<Button> button) {
    if (button->getToDraw())
        button->setColorText(255, 255, 255, 255);
//    this->selectedGame = "";
}

void MainMenu::displayServerPanelSprite(bool b) {
    auto window = this->manager.getWindow();

    window->getSpriteByName("panel")->setToDraw(b);
    if (b)
        window->getTextManager()->setColor("gameList", 255, 255, 255, 255);
    else
        window->getTextManager()->setColor("gameList", 255, 255, 255, 0);
}

void MainMenu::panelMode(bool b) {
    auto window = this->manager.getWindow();
    window->getSpriteByName("header")->setToDraw(!b);
    getButtonByName("singlePlayer")->setToDraw(!b);
    getButtonByName("multiPlayer")->setToDraw(!b);
    getButtonByName("options")->setToDraw(!b);
    getButtonByName("quit")->setToDraw(!b);
    if (!b)
        window->getTextManager()->setColor("title", "white");
    else
        window->getTextManager()->setColor("title", 255, 255, 255, 0);
    this->splash.switching(!b);
}

void MainMenu::addButton(std::string buttonName, const std::string &sprite) {
    this->buttons.insert(std::pair<std::string, std::shared_ptr<Button>>(buttonName, std::make_shared<Button>(
            Button(this->manager.getWindow(), sprite, buttonName, []() {}, []() {}, []() {}))));
}

void MainMenu::onReleaseServerButtons(std::string serverName) {
    getButtonByName(serverName)->setOnReLease([serverName, this]() {
        Logger::log(Logger::LogType::info, serverName + " released");
        getButtonByName(serverName)->setColorText(255, 102, 0, 255);
        this->selectedGame = serverName;
        for (const auto &serv : this->game->getGameList())
            if (serv != serverName)
                getButtonByName(serv)->setColorText(255, 255, 255, 255);
    });
}

void MainMenu::ipInputDisplay(bool b) {
    panelMode(b);
    backButtonDisplay(b);
    auto window = this->manager.getWindow();
    if (!buttonExist("joinServer") && b) {
        window->addSprite("input_button", "inputIp");
        window->getSpriteByName("inputIp")->setScale({0.6, 0.4});
        window->getSpriteByName("inputIp")->setPosition({400, 300});
        addButton("joinServer", "button");
        getButtonByName("joinServer")->setPosition({500, 400});
        getButtonByName("joinServer")->setText("JOIN SERVER", 25, "white");
        getButtonByName("joinServer")->setPosText({getButtonByName("joinServer")->getPosition().x + 45, getButtonByName("joinServer")->getPosition().y + 40});
        getButtonByName("joinServer")->setColorText(255, 255, 255, 255);
        getButtonByName("joinServer")->setOnReLease([this]() {
            ipInputDisplay(false);
            createJoinButtonDisplay(true);
            this->ipToConnect = gfx::InputEvent::clear();
            Logger::log(Logger::LogType::info, "You entered: " + this->ipToConnect);
        });
    }
    else {
        window->getSpriteByName("inputIp")->setToDraw(b);
        getButtonByName("joinServer")->setToDraw(b);
    }
    if (!b) {
        this->manager.getWindow()->getTextManager()->setText("serverip", "");
    }
    this->drawIp = b;
}

void MainMenu::createJoinButtonDisplay(bool b) {
    panelMode(b);
    if (!buttonExist("create")) {
        addButton("create", "button");
        getButtonByName("create")->setPosition({static_cast<float>(this->manager.getWindow()->getSize().x) / 2 - 284, static_cast<float>(this->manager.getWindow()->getSize().y) / 2 - 50});
        getButtonByName("create")->setText("CREATE", 25, "white");
        getButtonByName("create")->setColorText(255, 255, 255, 255);
        getButtonByName("create")->setPosText({getButtonByName("create")->getPosition().x + 87, getButtonByName("create")->getPosition().y + 40});
        getButtonByName("create")->setOnReLease([this]() {
            createJoinButtonDisplay(false);
            createInputDisplay(true);
        });

        addButton("join", "button");
        getButtonByName("join")->setPosition({static_cast<float>(this->manager.getWindow()->getSize().x) / 2 + 15, static_cast<float>(this->manager.getWindow()->getSize().y) / 2 - 50});
        getButtonByName("join")->setText("JOIN", 25, "white");
        getButtonByName("join")->setColorText(255, 255, 255, 255);
        getButtonByName("join")->setPosText({getButtonByName("join")->getPosition().x + 100, getButtonByName("join")->getPosition().y + 40});
        this->getButtonByName("join")->setOnReLease([this](){
            createJoinButtonDisplay(false);
            displayServerList(true);
        });
    }
    else {
        getButtonByName("create")->setToDraw(b);
        getButtonByName("join")->setToDraw(b);
    }
    backButtonDisplay(true);
}

void MainMenu::displayServerList(bool b) {
    gfx::Vector2Float pos = {490, 210};
    Logger::log(Logger::LogType::info, "MULTIPLAYER RELEASED");
    panelMode(b);
    if (b) {
        try {
            this->game = std::make_shared<GameBase>(GameBase(this->ipToConnect, 50000, this->_evtMgr, 25565, 25566));
        } catch (...) {
            MainMenu menu;
            menu.launch();
            std::_Exit(0);
        }
    }
    displayServerPanelSprite(b);
    if (!buttonExist("joinGame") && b) {
        for (const std::string &serverName : this->game->getGameList()) {
            std::cout << "ServrName" << serverName << std::endl;
            addButton(serverName, "server_button");
            getButtonByName(serverName)->setText(serverName, 20, "white");
            getButtonByName(serverName)->setColorText(255, 255, 255, 255);
            getButtonByName(serverName)->setPosition(pos);
            getButtonByName(serverName)->setPosText({pos.x + 40, pos.y + 20});
            onReleaseServerButtons(serverName);
            pos.y += 75;
        }
        addButton("joinGame", "small_button");
        getButtonByName("joinGame")->setText("Join", 22, "white");
        getButtonByName("joinGame")->setColorText(255, 255, 255, 255);
        getButtonByName("joinGame")->setPosition({580, 595});
        getButtonByName("joinGame")->setPosText({610, 605});
        onReleaseJoinGameButton();
    }
    else {
        getButtonByName("joinGame")->setToDraw(b);
        for (const std::string &serverName : this->game->getGameList())
            getButtonByName(serverName)->setToDraw(b);
    }
}

void MainMenu::onReleaseBackButton() {
    getButtonByName("back")->setOnReLease([this]() {
        if (buttonExist("joinServer") && getButtonByName("joinServer")->getToDraw())
            ipInputDisplay(false);
        else if (buttonExist("create") && getButtonByName("create")->getToDraw())
            createJoinButtonDisplay(false);
        else if (buttonExist("createGame") && getButtonByName("createGame")->getToDraw())
            createInputDisplay(false);
        else if (buttonExist("joinGame") && getButtonByName("joinGame")->getToDraw())
            displayServerList(false);
        else if (buttonExist("upButton"))
        	showOptionsMenu(false);
        getButtonByName("back")->setToDraw(false);
    });
}

bool MainMenu::buttonExist(const std::string &name) {
    auto it = this->buttons.find(name);
    return !(it == this->buttons.end());
}

void MainMenu::backButtonDisplay(bool b) {
    if (!buttonExist("back")) {
        this->buttons.insert(std::make_pair<std::string, std::shared_ptr<Button>>("back", std::make_shared<MenuButton>(MenuButton(this->manager.getWindow(), "button4", "back", [](){}, [](){}, [](){}))));
        getButtonByName("back")->setCenter({182, 0});
        getButtonByName("back")->setPosition({static_cast<float>(this->manager.getWindow()->getSize().x), static_cast<float>(this->manager.getWindow()->getSize().y) - 60});
        getButtonByName("back")->setText("BACK", 25, "white");
        onReleaseBackButton();
    }
    else
        getButtonByName("back")->setToDraw(b);
}

void MainMenu::createInputDisplay(bool b) {
    auto window = this->manager.getWindow();
    panelMode(b);
    if (!buttonExist("createGame") && b) {
        window->addSprite("input_button", "inputGameName");
        window->getSpriteByName("inputGameName")->setScale({0.6, 0.4});
        window->getSpriteByName("inputGameName")->setPosition({400, 200});

        window->addSprite("input_button", "inputPwd");
        window->getSpriteByName("inputPwd")->setScale({0.6, 0.4});
        window->getSpriteByName("inputPwd")->setPosition({400, 300});

        addButton("createGame", "button");


        getButtonByName("createGame")->setPosition({500, 400});
        getButtonByName("createGame")->setText("CREATE GAME", 25, "white");
        getButtonByName("createGame")->setPosText({getButtonByName("createGame")->getPosition().x + 45,
                                                   getButtonByName("createGame")->getPosition().y + 40});
        getButtonByName("createGame")->setColorText(255, 255, 255, 255);
        getButtonByName("createGame")->setOnReLease([this]() {
            createInputDisplay(false);
            this->manager.getWindow()->getTextManager()->setText("pwd", "");
            this->manager.getWindow()->getTextManager()->setText("serverName", "");
            Logger::log(Logger::LogType::info, "Game name : " + this->gameNameInput);
            Logger::log(Logger::LogType::info, "Password : " + this->pwdInput);
            this->createGame = true;
        });
    } else {
        window->getSpriteByName("inputGameName")->setToDraw(b);
        window->getSpriteByName("inputPwd")->setToDraw(b);
        getButtonByName("createGame")->setToDraw(b);
    }
}

void MainMenu::pwdJoinInputDisplay(bool b) {
    panelMode(b);
    auto window = this->manager.getWindow();

    if (!buttonExist("connect") && b) {

        window->addSprite("input_button", "pwdConnect");
        window->getSpriteByName("pwdConnect")->setScale({0.6, 0.4});
        window->getSpriteByName("pwdConnect")->setPosition({400, 300});
        addButton("joinGameWithPwd", "button");

        getButtonByName("joinGameWithPwd")->setPosition({500, 400});
        getButtonByName("joinGameWithPwd")->setText("JOIN SERVER", 25, "white");
        getButtonByName("joinGameWithPwd")->setPosText({getButtonByName("joinGameWithPwd")->getPosition().x + 45, getButtonByName("joinGameWithPwd")->getPosition().y + 40});
        getButtonByName("joinGameWithPwd")->setColorText(255, 255, 255, 255);
        getButtonByName("joinGameWithPwd")->setOnReLease([this]() {
            this->joinPwdGame = true;
        });
    }
    else {
        window->getSpriteByName("pwdConnect")->setToDraw(b);
        getButtonByName("joinGameWithPwd")->setToDraw(b);
    }
    if (!b) {
        this->manager.getWindow()->getTextManager()->setText("serverip", "");
    }
    this->drawIp = b;
}

void MainMenu::showOptionsMenu(bool b)
{
	panelMode(b);
	backButtonDisplay(b);
	auto window = this->manager.getWindow();
	if (!buttonExist("upButton") && b) {


		addButton("VolumePlus", "button");
		auto volumePlusButton = getButtonByName("VolumePlus");
		volumePlusButton->setPosition({800, 200});
		volumePlusButton->setText("Volume +", 25, "white");
		volumePlusButton->setPosText({volumePlusButton->getPosition().x + 20, volumePlusButton->getPosition().y + 40});

		volumePlusButton->setOnReLease([this]() {
		});


		addButton("VolumeDown", "button");
		auto volumeDownButton = getButtonByName("VolumeDown");
		volumeDownButton->setPosition({800, 400});
		volumeDownButton->setText("Volume -", 25, "white");
		volumeDownButton->setPosText({volumeDownButton->getPosition().x + 20, volumeDownButton->getPosition().y + 40});

		volumeDownButton->setOnReLease([this]() {
		});


		window->addSprite("input_button", "downKeyInput");
		window->getSpriteByName("downKeyInput")->setScale({0.2, 0.5});
		window->getSpriteByName("downKeyInput")->setPosition({350, 20});

		addButton("downButton", "button");
		auto downButton = getButtonByName("downButton");
		downButton->setPosition({240, 10});

		downButton->setText("Down", 25, "white");
		downButton->setScale({0.4, 0.9});
		downButton->setPosText({downButton->getPosition().x + 40, downButton->getPosition().y + 40});
		downButton->setColorText(255, 255, 255, 255);


		window->addSprite("input_button", "upKeyInput");
		window->getSpriteByName("upKeyInput")->setScale({0.2, 0.5});
		window->getSpriteByName("upKeyInput")->setPosition({350, 180});
		addButton("upButton", "button");

		auto UpButton = getButtonByName("upButton");
		UpButton->setPosition({240, 170});

		UpButton->setText("UP", 25, "white");
		UpButton->setScale({0.4, 0.9});
		UpButton->setPosText({UpButton->getPosition().x + 45, UpButton->getPosition().y + 40});
		UpButton->setColorText(255, 255, 255, 255);


		window->addSprite("input_button", "leftKeyInput");
		window->getSpriteByName("leftKeyInput")->setScale({0.2, 0.5});
		window->getSpriteByName("leftKeyInput")->setPosition({350, 330});

		addButton("leftButton", "button");
		auto leftButton = getButtonByName("leftButton");
		leftButton->setPosition({240, 325});

		leftButton->setText("Left", 25, "white");
		leftButton->setScale({0.4, 0.9});
		leftButton->setPosText({leftButton->getPosition().x + 20, leftButton->getPosition().y + 40});
		leftButton->setColorText(255, 255, 255, 255);



		window->addSprite("input_button", "rightKeyInput");
		window->getSpriteByName("rightKeyInput")->setScale({0.2, 0.5});
		window->getSpriteByName("rightKeyInput")->setPosition({350, 480});

		addButton("rightButton", "button");
		auto rightButton = getButtonByName("rightButton");
		rightButton->setPosition({240, 470});

		rightButton->setText("right", 25, "white");
		rightButton->setScale({0.4, 0.9});
		rightButton->setPosText({rightButton->getPosition().x + 20, rightButton->getPosition().y + 40});
		rightButton->setColorText(255, 255, 255, 255);



		window->addSprite("input_button", "shootKeyInput");
		window->getSpriteByName("shootKeyInput")->setScale({0.2, 0.5});
		window->getSpriteByName("shootKeyInput")->setPosition({350, 625});

		addButton("shootButton", "button");
		auto shootButton = getButtonByName("shootButton");
		shootButton->setPosition({240, 615});

		shootButton->setText("shoot", 25, "white");
		shootButton->setScale({0.4, 0.9});
		shootButton->setPosText({shootButton->getPosition().x + 20, shootButton->getPosition().y + 40});
		shootButton->setColorText(255, 255, 255, 255);

	}
	else {
			window->getSpriteByName("upKeyInput")->setToDraw(b);
			getButtonByName("upButton")->setToDraw(b);

			window->getSpriteByName("leftKeyInput")->setToDraw(b);
			getButtonByName("leftButton")->setToDraw(b);

			window->getSpriteByName("rightKeyInput")->setToDraw(b);
			getButtonByName("rightButton")->setToDraw(b);

			window->getSpriteByName("downKeyInput")->setToDraw(b);
			getButtonByName("downButton")->setToDraw(b);

			window->getSpriteByName("shootKeyInput")->setToDraw(b);
			getButtonByName("shootButton")->setToDraw(b);

		getButtonByName("VolumeDown")->setToDraw(b);
				getButtonByName("VolumePlus")->setToDraw(b);

		manager.getWindow()->getTextManager()->setText("downKeyInput", "");
		manager.getWindow()->getTextManager()->setText("leftKeyInput", "");
		manager.getWindow()->getTextManager()->setText("rightKeyInput", "");
		manager.getWindow()->getTextManager()->setText("upKeyInput", "");
		manager.getWindow()->getTextManager()->setText("shootKeyInput", "");

	}

}

void MainMenu::changeKeyBindingsEvent(const gfx::MouseReleaseEvent &event)
{
	this->gameNameInputReleased = false;
	this->pwdInputReleased = false;
	this->drawServerName = false;
	this->drawPwd = false;
	_downInputReleased = false;
	_leftInputReleased = false;
	_rightInputReleased = false;
	_shootInputRelased = false;
	_upInputReleased = false;

	if (this->manager.getWindow()->getSpriteByName("upKeyInput") != nullptr && this->manager.getWindow()->getSpriteByName("upKeyInput")->getToDraw() && isInBoundsSprite("upKeyInput", event.getPosition()))
		_upInputReleased = true;

	else if (this->manager.getWindow()->getSpriteByName("downKeyInput") != nullptr && this->manager.getWindow()->getSpriteByName("downKeyInput")->getToDraw() && isInBoundsSprite("downKeyInput", event.getPosition()))
		_downInputReleased = true;

	else if (this->manager.getWindow()->getSpriteByName("leftKeyInput") != nullptr && this->manager.getWindow()->getSpriteByName("leftKeyInput")->getToDraw() && isInBoundsSprite("leftKeyInput", event.getPosition()))
		_leftInputReleased = true;

	else if (this->manager.getWindow()->getSpriteByName("rightKeyInput") != nullptr && this->manager.getWindow()->getSpriteByName("rightKeyInput")->getToDraw() && isInBoundsSprite("rightKeyInput", event.getPosition()))
		_rightInputReleased = true;

	else if (this->manager.getWindow()->getSpriteByName("shootKeyInput") != nullptr && this->manager.getWindow()->getSpriteByName("shootKeyInput")->getToDraw() && isInBoundsSprite("shootKeyInput", event.getPosition()))
		_shootInputRelased = true;

	gfx::InputEvent::clear();


}


