//
// Created by prat on 07/11/18.
//

#include "LOG/Logger.hpp"
#include "Exception.hpp"

/**
 * Constructor of Exception
 * @param msg Msg that is thrown
 */
rtype::Exception::Exception(std::string msg) : std::exception(), errorMsg(msg) {
    Logger::log(Logger::LogType::error, msg);
}

/**
 * Function that gets the error msg
 * @return the errorMsg
 */
const std::string rtype::Exception::getErrorMsg() const {
    return errorMsg;
}

const char *rtype::Exception::what() const noexcept
{
    return errorMsg.data();
}