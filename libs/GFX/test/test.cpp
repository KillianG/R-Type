//
// Created by killian on 02/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <GFX/GfxManager.hpp>
#include <GFX/KeyboardManager.hpp>
#include <thread>
#include <GFX/TextManager.hpp>
//#include <libs/GFX/KeyboardManager.hpp>
//#include <libs/GFX/GfxManager.hpp>
//#include <libs/GFX/Sprite.hpp>
//#include <libs/GFX/Events.hpp>
#include "catch.hpp"

TEST_CASE("GfxManager", "[GFX]") {
    SECTION("Creation") {
        gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
        gfx::Manager &manager2 = gfx::Singleton<gfx::Manager>::get();
        REQUIRE(&manager == &manager2);
        REQUIRE(gfx::Manager::colors.size() == 7);
        REQUIRE(manager.getWindow() == nullptr);
    }
    SECTION("Mutex") {
        gfx::Manager &manager = gfx::Manager::get();
        std::thread create1([&manager](){manager.new_window("TEST", {42, 69});});
        std::thread create2([&manager](){manager.new_window("TEST2", {1080, 720});});
        create1.join();
        create2.join();
        REQUIRE(manager.getWindows().size() == 2);
        REQUIRE(manager.getWindow()->getSize().x == 1080);
        REQUIRE(manager.getWindow()->getSize().y == 720);
        std::thread close1([&manager](){manager.close_window();});
        std::thread close2([&manager](){manager.close_window();});
        close1.join();
        close2.join();
    }
}

TEST_CASE("Windows", "[GFX]") {
    SECTION("Creation") {
        gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
        manager.new_window("TEST", {1080, 720});

        REQUIRE(manager.getWindow() != nullptr);
        REQUIRE(manager.getWindows().size() == 1);

        REQUIRE_NOTHROW(manager.setBackgroundColor("red"));

        REQUIRE_THROWS(manager.setBackgroundColor("NO_COLOR"));

        SECTION("Deletion") {
            manager.close_window();

            REQUIRE(manager.getWindows().size() == 0);
            REQUIRE(manager.getWindow() == nullptr);
        }
    }
}

TEST_CASE("Sprites", "[GFX]") {
    SECTION("Adding") {
        gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
        gfx::KeyboardManager kbman;

        manager.new_window("TEST", {1080, 720});

        REQUIRE(manager.getWindow() != nullptr);
        REQUIRE(manager.getWindows().size() == 1);

        manager.getWindow()->addSprite("ship", "ship");
//        manager.getWindow()->getSpriteByName("ship")->clip({0, 0}, {32, 26});

        REQUIRE(manager.getWindow()->getSpriteByName("ship") != nullptr);
        REQUIRE(manager.getWindow()->getSpriteByName("NO_NAME") == nullptr);

        manager.getWindow()->getSpriteByName("ship")->setScale({2, 2});

        while (!kbman.isKeyPressed("Escape")) {
            if (kbman.isKeyPressed("Z"))
                manager.getWindow()->getSpriteByName("ship")->move(gfx::direction::UP, 2);
            if (kbman.isKeyPressed("S"))
                manager.getWindow()->getSpriteByName("ship")->move(gfx::direction::DOWN, 2);
            if (kbman.isKeyPressed("Q"))
                manager.getWindow()->getSpriteByName("ship")->move(gfx::direction::LEFT, 2);
            if (kbman.isKeyPressed("D"))
                manager.getWindow()->getSpriteByName("ship")->move(gfx::direction::RIGHT, 2);

            manager.run();
        }
        manager.close_window();
        REQUIRE(manager.getWindows().size() == 0);
    }
}

TEST_CASE("Mouse", "[GFX]") {
    gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
    manager.new_window("TEST", {1080, 720});
    REQUIRE(manager.getMouse() != nullptr);
    REQUIRE(manager.getMouse()->getPosition().x >= 0);
    REQUIRE(manager.getMouse()->getPosition().y >= 0);
    REQUIRE(manager.getMouse()->isButtonPressed(gfx::Mouse::LEFT) == false);
    manager.getMouse()->setPosition({10, 30});
    REQUIRE(manager.getMouse()->getPosition().x == 10);
    REQUIRE(manager.getMouse()->getPosition().y == 30);
    manager.getMouse()->setPosition({45, 70}, *manager.getWindow());
    REQUIRE(manager.getMouse()->getPosition(*manager.getWindow()).x == 45);
    REQUIRE(manager.getMouse()->getPosition(*manager.getWindow()).y == 70);
}

TEST_CASE("Music", "[GFX]") {
    gfx::SoundManager sounder;
    gfx::KeyboardManager kbman;
    sounder.addMusic("boom", "FTLCosmos");
    sounder.playMusic("boom");
    sounder.setLoopMusic("boom", true);
    gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
    manager.new_window("T", {1080, 720});
    while (!kbman.isKeyPressed("Escape")) {
        manager.run();
    }

    Logger::close();
}

/*TEST_CASE("Text", "[GFX]") {
    gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
    gfx::KeyboardManager kbman;
    manager.new_window("TEST", {1080, 720});
    manager.getWindow()->getTextManager()->loadFont("arial", "assets/arial.ttf");
    manager.getWindow()->getTextManager()->addText("arial", 15, "SALUT", "salut");
    manager.getWindow()->getTextManager()->setPosition("salut", {50, 300});
    manager.getWindow()->getTextManager()->setColor("salut", "red");
    manager.setBackgroundColor("blue");
    auto size = manager.getWindow()->getTextManager()->getSize("salut");

    std::cout << size.x << " ; " << size.y << std::endl;
    while (!kbman.isKeyPressed("E")){
        manager.run();
    }
}*/

class TestReceiver : public Receiver<TestReceiver> {
public:
    TestReceiver() {
        _evtMgr.subscribe<gfx::ClickEvent>(*this);
    }

public:
    EventManager _evtMgr {};
    void receive(const gfx::InputEvent event) {
        std::cout << gfx::InputEvent::input << std::endl;
    }
    void receive(const gfx::ClickEvent event) {
        std::cout << event.getPosition().x << " ; " << event.getPosition().y << std::endl;
        std::cout << "\033[1;33m" << __PRETTY_FUNCTION__ << "\033[0m" << std::endl;
    };
};

#include "iostream"
TEST_CASE("Events", "[GFX]") {
    SECTION("Events") {
        gfx::Manager &manager = gfx::Singleton<gfx::Manager>::get();
        gfx::KeyboardManager kbman;
        TestReceiver receiver;
        receiver._evtMgr.subscribe<gfx::ClickEvent>(receiver);
        receiver._evtMgr.subscribe<gfx::InputEvent>(receiver);
        manager.new_window("TEST", {1080, 720}, receiver._evtMgr);
        while (!kbman.isKeyPressed("E")){
            manager.run();
        }
        std::cout << gfx::InputEvent::clear() << std::endl;
    }
}