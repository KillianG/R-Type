//
// Created by prat on 05/11/18.
//

#define CATCH_CONFIG_MAIN

#include <LOG/Logger.hpp>
#include "catch.hpp"

std::string getLastMsg(std::string logs) {
    std::string lastMsg;
    logs.replace(logs.find_last_of('\n'), 1, "");
    if (std::count(logs.begin(), logs.end(), '\n') != 0) {
        lastMsg = logs.substr(logs.find_last_of('\n'));
        lastMsg.replace(lastMsg.find_first_of('\n'), 1, "");
    }
    else
        lastMsg = logs;
    lastMsg = lastMsg.substr(lastMsg.find_first_of(' ') + 1);
    return lastMsg;
}

TEST_CASE("Logger") {
    SECTION("Creation") {
        const std::string firstLog = "I'll be back";
        const std::string secondLog = "I see dead people";
        const std::string thirdLog = "May the force be with you";

#ifdef __unix__
        Logger::log(Logger::LogType::warn, firstLog);
        REQUIRE(getLastMsg(Logger::getLogs()) == firstLog);

        Logger::log(Logger::LogType::info , secondLog);
        REQUIRE(getLastMsg(Logger::getLogs()) == secondLog);

        Logger::log(Logger::LogType::debug, thirdLog);
        REQUIRE(getLastMsg(Logger::getLogs()) == thirdLog);
#endif
    }
    SECTION("CLOSE") {
        Logger::close();
    }
}