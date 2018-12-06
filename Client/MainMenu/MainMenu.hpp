//
// Created by prat on 12/11/18.
//

#ifndef R_TYPE_MAINMENU_HPP
#define R_TYPE_MAINMENU_HPP

#include <Client/OptionsMenu/OptionsMenu.hpp>
#include "GfxManager.hpp"
#include "libs/EventManager/Receiver.hpp"
#include "libs/EventManager/EventManager.hpp"
#include "Button.hpp"
#include "Splash.hpp"
#include "../../libs/EventManager/EventManager.hpp"
#include "../../libs/GFX/Events.hpp"
#include "../../libs/GFX/GfxManager.hpp"
#include "../game/Game.hpp"

/**
 *  Main Menu class that displays the menu windows.
 *  Each event will be called from there.
 */

namespace fs = std::experimental::filesystem;

class MainMenu : public Receiver<MainMenu> {
public:
    MainMenu();
    ~MainMenu() = default;
    void launch();
    void receive(gfx::ClickEvent event);
    void receive(gfx::MouseReleaseEvent event);
    void receive(gfx::MouseMoveEvent event);
    void receive(gfx::InputEvent event);

    EventManager _evtMgr {};
private:

	using clock = std::chrono::steady_clock;
	void showOptionsMenu(bool b);

	void doThisEveryMs(int ms, std::function<void ()> f);

	std::string passwd;

	void playCinematic();
	bool stopCinem { false };
    std::shared_ptr<GameBase> game;
    bool createGame;
    bool joinPwdGame;
    void onReleaseSinglePlayerButton();
    void onReleaseMultiPlayerButton();
    void onReleaseOptionsButton();
    void onReleaseJoinGameButton();
    void onReleaseBackButton();
    void setButtons();
    void setSprites();
    void onReleaseQuitButton();
    void reset(std::shared_ptr<Button> button);
    void animation();
    bool isInBounds(std::shared_ptr<Button> button, gfx::Vector2I pos);
    bool isInBoundsSprite(std::string spriteName, gfx::Vector2I pos);
    void displayServerPanelSprite(bool b);
    void displayServerList(bool b);
    void panelMode(bool b);
    void addButton(std::string buttonName, const std::string &sprite);
    void onReleaseServerButtons(std::string serverName);
    void createJoinButtonDisplay(bool b);
    void backButtonDisplay(bool b);
    void ipInputDisplay(bool b);
    void createInputDisplay(bool b);
    void pwdJoinInputDisplay(bool b);
    bool buttonExist(const std::string &name);
    std::shared_ptr<Button> getButtonByName(const std::string &name);
    gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
    std::unordered_map<std::string, std::shared_ptr<Button>> buttons;
    Splash splash;
    bool quit;
    bool drawIp;
    bool drawJoinPwd;
    bool drawServerName;
    bool drawPwd;
    bool gameNameInputReleased;
    bool pwdInputReleased;
    bool _upInputReleased;
    bool _downInputReleased;
    bool _leftInputReleased;
    bool _rightInputReleased;
    bool _shootInputReleased;

    std::string _upInput;
    std::string _downInput;
    std::string _rightInput;
    std::string _leftInput;
    std::string _shootInput;
    std::string gameNameInput;
    std::string pwdInput;
    std::string pwdJoinInput;
    std::string ipToConnect;
    std::string selectedGame;
    std::string buttonPressed;
    float volume;

    void changeKeyBindingsEvent(const gfx::MouseReleaseEvent &event);


    std::vector<std::string> serverExamples {"MonServeurMinecraft", "LaCaveDeMaxence", "Minefield", "PINE", "MeletClonesGame"};
};


#endif //R_TYPE_MAINMENU_HPP