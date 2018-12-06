//
// Created by prat on 05/11/18.
//

#include "Logger.hpp"
#include <iostream>
#include <chrono>

std::fstream Logger::myFile;
const std::map<Logger::LogType, const std::string> Logger::logTypeMap = {
        {Logger::LogType::debug, "Debug"},
        {Logger::LogType::error, "Error"},
        {Logger::LogType::info, "Info"},
        {Logger::LogType::warn, "Warn"}
};

/**
 * Function that writes the log type and msg in log.txt then prints it
 * @param type Type of the message
 * @param msg Output message
 */
void Logger::log(Logger::LogType type, const std::string &msg) {
#ifdef __unix__
    auto currentTime = getTime();
#else
    std::string currentTime("");
#endif

    std::string printableType = getType(type);
    if (!Logger::myFile.is_open()) {
        Logger::myFile.open("log.txt", std::ios_base::app);
        Logger::myFile << "--------------------------------------------" << std::endl;
    }
    Logger::myFile << "[" << currentTime << "][" << printableType << "] " << msg << std::endl;
    std::cout << "[" << currentTime << "][" << printableType << "] " << msg << std::endl;
}

#ifdef __unix__
/**
 * Function that gives the current time hh:mm:ss
 * @return The current time
 */
std::_Put_time<char> Logger::getTime() {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    auto currentTime = std::put_time(std::localtime(&now_c), "%T");
    return (currentTime);
}
#endif

/**
 * Function that gives the correct type to output giving a Logger::LogType
 * @param type Type of the message
 * @return The string as associated with the Logger::LogType
 */
std::string Logger::getType(Logger::LogType type) {
    return Logger::logTypeMap.find(type)->second;
}

#ifdef __unix__
/**
 * Function that gets the logs of the entire file
 * @return a string of the logs
 */
std::string Logger::getLogs() {
    std::ifstream logFile("log.txt");
    std::stringstream logString;
    logString << logFile.rdbuf();
    logFile.close();
    return logString.str();
}
#endif

/**
 * Function that closes the file
 * For performance issue, you should call it only once at the end of the program
 */
void Logger::close() {
    Logger::myFile.close();
}