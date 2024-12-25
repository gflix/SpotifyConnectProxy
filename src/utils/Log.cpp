#include <stdio.h>
#include <unistd.h>
#include <systemd/sd-daemon.h>
#include <ctime>
#include <iostream>
#include <utils/Log.hpp>

Log Log::instance = Log();

Log::Log(LogLevel logLevel):
    m_toTty(true),
    m_logLevel(logLevel)
{
    determineOutputMode();
}

Log::~Log()
{
}

void Log::error(const std::string& logMessage)
{
    if (LogLevel::ERROR <= m_logLevel) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_toTty) {
            std::cerr << "\033[31;1m" << getTimestamp(time(nullptr)) << " [E] " << logMessage << "\033[0m" << std::endl;
        } else {
            std::cerr << SD_ERR << logMessage << std::endl;
        }
    }
}

void Log::warning(const std::string& logMessage)
{
    if (LogLevel::WARNING <= m_logLevel) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_toTty) {
            std::cerr << "\033[33;1m" << getTimestamp(time(nullptr)) << " [W] " << logMessage << "\033[0m" << std::endl;
        } else {
            std::cerr << SD_WARNING << logMessage << std::endl;
        }
    }
}

void Log::notice(const std::string& logMessage)
{
    if (LogLevel::NOTICE <= m_logLevel) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_toTty) {
            std::cout << "\033[1m" << getTimestamp(time(nullptr)) << " [N] " << logMessage << "\033[0m" << std::endl;
        } else {
            std::cerr << SD_NOTICE << logMessage << std::endl;
        }
    }
}

void Log::info(const std::string& logMessage)
{
    if (LogLevel::INFO <= m_logLevel) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_toTty) {
            std::cout << getTimestamp(time(nullptr)) << " [I] " << logMessage << std::endl;
        } else {
            std::cerr << SD_INFO << logMessage << std::endl;
        }
    }
}

void Log::debug(const std::string& logMessage)
{
    if (LogLevel::DEBUG <= m_logLevel) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_toTty) {
            std::cout << "\033[34;2m" << getTimestamp(time(nullptr)) << " [D] " << logMessage << "\033[0m" << std::endl;
        } else {
            std::cerr << SD_DEBUG << logMessage << std::endl;
        }
    }
}

void Log::setLogLevel(LogLevel logLevel)
{
    m_logLevel = logLevel;
}

LogLevel Log::logLevel(void) const
{
    return m_logLevel;
}

std::string Log::getTimestamp(time_t timestamp)
{
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));

    return buffer;
}

void Log::determineOutputMode(void)
{
    m_toTty = isatty(fileno(stdout)) && isatty(fileno(stderr));
}
