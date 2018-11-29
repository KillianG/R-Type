//
// Created by prat on 05/11/18.
//

#ifndef R_TYPE_LOGGER_HPP
#define R_TYPE_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

class Logger {
public:
    Logger() = delete;
    ~Logger() = delete;

    enum class LogType {info, debug, warn, error};
    static void log(LogType type, const std::string &msg);
    static std::string getLogs();
    static void close();
private:
    static std::_Put_time<char> getTime();
    static std::string getType(LogType type);
    static std::fstream myFile;
    static const std::map<LogType, const std::string> logTypeMap;
};


#endif //R_TYPE_LOGGER_HPP
