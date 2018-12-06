//
// Created by killian on 16/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#include "Game.hpp"
#include <chrono>
#include "../../libs/LOG/Logger.hpp"
#include "../../libs/GFX/GfxManager.hpp"

/**
 * check the connection between client and server
 * @return true if connected false if not
 */
bool GameBase::checkConnection() {
    static std::chrono::milliseconds lag(0);
    std::chrono::milliseconds timeStep(3000);
    static clock::time_point start(clock::now());

    auto deltaTime = clock::now() - start;
    start = clock::now();
    lag += std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);

    if (lag > timeStep) {
        lag -= timeStep;
        return rfcClientUdp->isGameConnected(5);
    }
    return true;
}

/**
 * check the dead sprites to be removed
 * @param gfx the gfxManager
 */
void GameBase::checkDeads(gfx::Manager &gfx) {
    auto stupidDeadPlayerOrEnnemy = rfcClientUdp->getDeadRat();
    auto stupidRemoveSprite = rfcClientUdp->getRemove();

    for (auto &&dead : stupidRemoveSprite) {
        auto name = std::to_string(dead);
        if (gfx.getWindow()->getSpriteByName(name) != nullptr) {
            gfx.getWindow()->getSpriteByName(name)->setToDraw(false);
        }
    }

    for (auto &&dead : stupidDeadPlayerOrEnnemy) {
        auto name = std::to_string(dead);
        if (gfx.getWindow()->getSpriteByName(name) != nullptr) {
            this->soundBoom.play();
            this->deads.push_back({dead, gfx.getWindow()->getSpriteByName(name)->getPosition().x, gfx.getWindow()->getSpriteByName(name)->getPosition().y, 0});
            gfx.getWindow()->getSpriteByName(name)->setToDraw(false);
        }
    }

    this->doThisEveryMs(10, [this](){
        static gfx::Manager &gfx = gfx::Manager::get();

        for (auto &&dead : this->deads) {
            if (dead.current_anim == 0) {
                gfx.getWindow()->addSprite("explosion10_63x100x63", "explosion" + std::to_string(dead.id));
                gfx.getWindow()->getSpriteByName("explosion" + std::to_string(dead.id))->setPosition({dead.x, dead.y});
                gfx.getWindow()->getSpriteByName("explosion" + std::to_string(dead.id))->setScale({1, 1});
            }
            auto sprite = gfx.getWindow()->getSpriteByName("explosion" + std::to_string(dead.id));
            if (sprite == nullptr)
                break;
            sprite->clip({0, 101 * dead.current_anim}, {101, 101});
            dead.current_anim += 1;
            if (dead.current_anim >= 63) {
                gfx.getWindow()->removeSprite("explosion" + std::to_string(dead.id));
                dead.current_anim = -1;
            }
        }
    });

    for (auto it = this->deads.begin(); it != this->deads.end(); it++) {
        if ((*it).current_anim == -1) {
            this->deads.erase(it);
            break;
        }
    }
}

/**
 * init the traductor
 */
void GameBase::initGameInfos() {
    auto infos = rfcClientUdp->getEntitiesInit();

    for (auto &&info : infos) {
        Logger::log(Logger::LogType::info, "Loading : " + info.to_str());
        this->traductor.insert(std::make_pair<std::string, std::string>(std::forward<std::string>(std::to_string(info.entityType)), std::forward<std::string>(info.path)));
        this->spriteTrad.insert(std::make_pair<std::string, GameBase::sizeSprite>(std::forward<std::string>(std::to_string(info.entityType)), std::forward<GameBase::sizeSprite>({info.sizeX, info.sizeY})));
    }
}

/**
 * check all entities to print or not
 * @param gfx the gfxManager
 */
void GameBase::checkEntities(gfx::Manager &gfx) {
    auto entities = rfcClientUdp->getEntitiesPos();
    std::vector<hitMarker> hitMarkers;
    hitMarker boss = {-100, -100, -100, -100};

    this->doThisEveryMs(50, [&gfx](){
        if (gfx.getWindow()->getSpriteByName("hitMarked") != nullptr)
            gfx.getWindow()->removeSprite("hitMarked");
    });

    this->doThisEveryMs(1, [this, entities](){
        static int allDead = 0;

        if (allDead == 100)
            this->isLost = true;

        for (auto &&entity : entities){
            if (entity.entityType >= 1 && entity.entityType <= 4) {
                allDead = 0;
                return;
            }
        }
        allDead++;
    });

    for (auto &&entity : entities) {
        auto spriteName = std::to_string(entity.entityId);
        auto sprite = gfx.getWindow()->getSpriteByName(spriteName);
        auto spriteSize = spriteTrad.find(std::to_string(entity.entityType));

        if (sprite == nullptr) {
            auto trad = traductor.find(std::to_string(entity.entityType));
            if (trad == traductor.end()) {
                break;
            }
            gfx.getWindow()->addSprite(trad->second, spriteName);
            sprite = gfx.getWindow()->getSpriteByName(spriteName);
            if (sprite == nullptr) {
                break;
            }
        }
        if (spriteSize != spriteTrad.end())
            sprite->clip({0, static_cast<int>(spriteSize->second.x * entity.animTime)}, {spriteSize->second.x, spriteSize->second.y});
        sprite->setPosition({static_cast<float>(entity.X), static_cast<float>(entity.Y)});
        auto ty = entity.entityType;
        if ((ty >= 5 && ty <= 9)) {
            hitMarkers.push_back({(float)entity.X, (float)entity.Y, spriteSize->second.x, spriteSize->second.y});
        } else if (ty == 18) {
            boss = {(float)entity.X, (float)entity.Y, spriteSize->second.x, spriteSize->second.y};
        }
        auto sprita = gfx.getWindow()->getSpriteByName("loadingWeapon");
        auto spritb = gfx.getWindow()->getSpriteByName("progressBorder");
        if (sprita == nullptr)
            gfx.getWindow()->addSprite("progress", "loadingWeapon");
        if (spritb == nullptr) {
            gfx.getWindow()->addSprite("progressBorder", "progressBorder");
            spritb = gfx.getWindow()->getSpriteByName("progressBorder");
            spritb->setScale({2, 2});
            spritb->setPosition({0, 685});
        }
        sprita = gfx.getWindow()->getSpriteByName("loadingWeapon");
        if (sprita != nullptr) {
            sprita->setScale({2, 2});
            sprita->setPosition({10, 688});
            sprita->clip({0, 0}, {17 * this->firePower, 32});
        }
    }
    if (boss.sizeY != -100) {
        for (auto &&hitMark : hitMarkers) {
            if (hitMark.posX  >= (boss.posX - 100)  && hitMark.posY >= (boss.posY - 100) && hitMark.posX <= (boss.posX + boss.sizeX) && hitMark.posY <= (boss.posY + boss.sizeY)){
                auto spriteHit = gfx.getWindow()->getSpriteByName("hitMarked");
                if (spriteHit == nullptr)
                    gfx.getWindow()->addSprite("hit", "hitMarked");
                spriteHit = gfx.getWindow()->getSpriteByName("hitMarked");
                if (spriteHit != nullptr)
                    spriteHit->setPosition({boss.posX, boss.posY});
            }
        }
    }
    if (this->isLost) {
        gfx::KeyboardManager kbman;
        while (!kbman.isKeyPressed("Escape")) {
            if (gfx.getWindow()->getSpriteByName("youdead") == nullptr)
                gfx.getWindow()->addSprite("You-Died", "youDead");
            gfx.run();
        }
        std::_Exit(0);
    }
}

void GameBase::checkLoad(gfx::Manager &gfx) {

}

void GameBase::doThisEveryMs(int ms, std::function<void()> f) {
    static std::chrono::milliseconds lag(0);
    std::chrono::milliseconds timeStep(ms);
    static clock::time_point start(clock::now());

    auto deltaTime = clock::now() - start;
    start = clock::now();
    lag += std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);

    if (lag > timeStep) {
        lag -= timeStep;
        f();
    }
}

/**
 * Most important function of the client, the on who runs everything
 * checkConnection, print sprites, getInfos from rfc etc...
 */
void GameBase::run() {
    gfx::Manager &gfx = gfx::Manager::get();
    Logger::log(Logger::LogType::info, "Running Game");
    gfx.getWindow()->clearAll();

    this->initGameInfos();
    gfx.getSoundManager().pauseMusic("ftl");
    gfx.getSoundManager().addMusic("fight", "fight");
    gfx.getSoundManager().playMusic("fight");

    while (true) {
        rfcClientUdp->checkGameRequest();
        this->checkDeads(gfx);
        this->checkEntities(gfx);
        this->checkButtons();
        this->checkLoad(gfx);

        gfx.run();
    }
}

std::vector<std::string> GameBase::getGameList() {
    return this->gamesList;
}

/**
 * Constructor for the game
 * @param ip the ip to connect
 * @param port the port
 * @param mgr the eventmanager
 */
GameBase::GameBase(std::string ip, int port, EventManager &mgr, int portUDP, int portTCP) : mgr(mgr) {
    std::string localGame("THESECRETNAMEOFTHELOCALGAMEYOUMISTNOTCREATETHESAME");
    this->firePower = 0;

    this->buffer.loadFromFile("assets/music/laser.ogg");
    this->sound.setBuffer(this->buffer);

    this->boomBuffer.loadFromFile("assets/music/boom.ogg");
    this->soundBoom.setBuffer(this->boomBuffer);

    this->bufferLASER.loadFromFile("assets/music/laserSTRONG.ogg");
    this->soundLASER.setBuffer(this->bufferLASER);

    this->bufferMEGALASER.loadFromFile("assets/music/laserMEGASTRONG.ogg");
    this->soundMEGALASER.setBuffer(this->bufferMEGALASER);

    clientUdp = std::shared_ptr<network::UdpSocket>(new network::UdpSocket(portUDP));
    rfcClientUdp = std::shared_ptr<network::MyRfcClient<network::UdpSocket>>(new network::MyRfcClient<network::UdpSocket>(*clientUdp));

    clientTcp = std::shared_ptr<network::TcpManager>(new network::TcpManager(portTCP));
    rfcClientTcp = std::shared_ptr<network::MyRfcClient<network::TcpManager>>(new network::MyRfcClient<network::TcpManager>(*clientTcp));

    std::string login = "killian";

    Logger::log(Logger::LogType::info, "Connecting to: " + ip + ":" + std::to_string(port));

    gamesList = rfcClientTcp->ConnectServer(ip, port, login);

    Logger::log(Logger::LogType::info, "Connected successfully");
}

/**
 * create a game on the server and connect to it
 * @param name the name of the game
 * @param password the password of the game
 */
void GameBase::createGame(std::string name, std::string password) {
    try {
        mgr.subscribe<gfx::ClickEvent>(*this);
        mgr.subscribe<gfx::KeyPressedEvent>(*this);
        mgr.subscribe<gfx::KeyReleasedEvent>(*this);
        auto info = rfcClientTcp->createGame(name, password);
        this->gameName = name;
        std::string login = "killian";
        Logger::log(Logger::LogType::info, "Login to new game at : " + info.ip + ":" + std::to_string(info.port));
        rfcClientUdp->FirstConnectToGame(info.ip, info.port, login);
        this->run();
    } catch (std::exception &e) {
    }
}

/**
 * join a game
 * @param name name of the game
 * @param password password of the game
 */
void GameBase::joinGame(std::string name, std::string password) {
    try {
        mgr.subscribe<gfx::ClickEvent>(*this);
        mgr.subscribe<gfx::KeyPressedEvent>(*this);
        mgr.subscribe<gfx::KeyReleasedEvent>(*this);
        this->gameName = name;
        auto info = rfcClientTcp->joinGame(name, password);
        std::string login = "killian";
        rfcClientUdp->FirstConnectToGame(info.ip, info.port, login);
        this->run();
    } catch (std::exception &e) {
    }
}

void GameBase::receive(gfx::ClickEvent event) {
}

void GameBase::receive(gfx::KeyPressedEvent event) {
    if (event.getKey() == "Escape") {
        rfcClientTcp->leave(this->gameName);
        std::_Exit(0);
    }
}

void GameBase::receive(gfx::KeyReleasedEvent event) {
    if (event.getKey() == "Space" && this->canShoot) {
        rfcClientUdp->fire(this->firePower);
        this->isCharging = false;
        if (this->firePower < 2)
            this->sound.play();
        else if (this->firePower == 2)
            this->soundLASER.play();
        else if (this->firePower > 2)
            this->soundMEGALASER.play();
        this->canShoot = false;
        this->firePower = 0;
    }
}

void GameBase::checkButtons() {
    static std::chrono::milliseconds lag(0);
    static std::chrono::milliseconds lagShoot(0);

    std::chrono::milliseconds timeStep(1000);
    std::chrono::milliseconds timeStepShoot(250);

    static clock::time_point start(clock::now());
    static clock::time_point startShoot(clock::now());

    auto deltaShoot = clock::now() - startShoot;
    startShoot = clock::now();
    lagShoot += std::chrono::duration_cast<std::chrono::milliseconds>(deltaShoot);
    if (lagShoot > timeStepShoot) {
        this->canShoot = true;
        lagShoot -= timeStepShoot;
    }

    if (_kbman.isKeyPressed("Z"))
        rfcClientUdp->movePlayer(network::playerMove::UP);
    if (_kbman.isKeyPressed("S"))
        rfcClientUdp->movePlayer(network::playerMove::DOWN);
    if (_kbman.isKeyPressed("Q"))
        rfcClientUdp->movePlayer(network::playerMove::LEFT);
    if (_kbman.isKeyPressed("D"))
        rfcClientUdp->movePlayer(network::playerMove::RIGHT);
    if (_kbman.isKeyPressed("Space")) {
        if (!this->isCharging) {
            start = clock::now();
            isCharging = true;
        }
        auto deltaTime = clock::now() - start;
        start = clock::now();
        lag += std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime);
        if (lag > timeStep) {
            if (this->firePower < 4) {
                this->firePower += 1;
                this->rfcClientUdp->chargeFire(this->firePower);
            }
            lag -= timeStep;
        }
    }
}
