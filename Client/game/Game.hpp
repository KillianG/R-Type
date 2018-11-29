//
// Created by killian on 16/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef RTYPE_LIBS_GAME_HPP
#define RTYPE_LIBS_GAME_HPP

#include "../../libs/Network/networkUtils.hpp"
#include "../../libs/Network/socket/include/UdpSocket.hpp"
#include "../../libs/Network/socket/include/TcpManager.hpp"
#include "../../libs/Network/RFC/MyRfcClient.hpp"
#include "../../libs/EventManager/EventManager.hpp"
#include "../../libs/GFX/Events.hpp"
#include "../../libs/GFX/KeyboardManager.hpp"
#include "../../libs/GFX/GfxManager.hpp"

class GameBase : public Receiver<GameBase> {

    struct dead {
        size_t id;
        float x;
        float y;
        int current_anim;
    };

    struct sizeSprite {
        int x;
        int y;
    };

public:

    using clock = std::chrono::steady_clock;

    GameBase(std::string ip, int port, EventManager &mgr, int portUDP, int portTCP);
    ~GameBase() = default;
    void createGame(std::string name, std::string password);
    void joinGame(std::string name, std::string password);
    void receive(gfx::ClickEvent event);
    void receive(gfx::KeyPressedEvent event);
    void receive(gfx::KeyReleasedEvent event);

    std::vector<std::string> getGameList();

private:

    bool checkConnection();
    void checkDeads(gfx::Manager &mgr);
    void checkEntities(gfx::Manager &mgr);
    void initGameInfos();

    void checkButtons();


    void doThisEveryMs(int ms, std::function<void()> f);
    void run();

    gfx::KeyboardManager _kbman;

    int firePower;

    std::unordered_map<std::string, GameBase::sizeSprite> spriteTrad;
    std::vector<GameBase::dead> deads;

    EventManager &mgr;
    std::shared_ptr<network::UdpSocket> clientUdp;
    std::shared_ptr<network::MyRfcClient<network::UdpSocket>> rfcClientUdp;
    std::shared_ptr<network::TcpManager> clientTcp;
    std::shared_ptr<network::MyRfcClient<network::TcpManager>> rfcClientTcp;
    std::vector<std::string> gamesList;
    std::unordered_map<std::string, std::string> traductor;
};


#else


class GameBase;


#endif //RTYPE_LIBS_GAME_HPP
