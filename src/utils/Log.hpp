#ifndef UTILS_LOG_HPP_
#define UTILS_LOG_HPP_

#include <ctime>
#include <mutex>
#include <sstream>
#include <string>
#include <models/LogLevel.hpp>

class Log
{
public:
    explicit Log(LogLevel logLevel = LogLevel::DEBUG);
    virtual ~Log();

    void error(const std::string& logMessage);
    void warning(const std::string& logMessage);
    void notice(const std::string& logMessage);
    void info(const std::string& logMessage);
    void debug(const std::string& logMessage);

    void setLogLevel(LogLevel logLevel);
    LogLevel logLevel(void) const;

    static Log instance;
    static std::string getTimestamp(time_t timestamp);

protected:
    bool m_toTty;
    LogLevel m_logLevel;
    std::mutex m_mutex;

    void determineOutputMode(void);
};


#define LOG_ERROR(message) { \
    std::stringstream tempLogStream; tempLogStream << message; ::Log::instance.error(tempLogStream.str()); \
}
#define LOG_WARNING(message) { \
    std::stringstream tempLogStream; tempLogStream << message; ::Log::instance.warning(tempLogStream.str()); \
}
#define LOG_NOTICE(message) { \
    std::stringstream tempLogStream; tempLogStream << message; ::Log::instance.notice(tempLogStream.str()); \
}
#define LOG_INFO(message) { \
    std::stringstream tempLogStream; tempLogStream << message; ::Log::instance.info(tempLogStream.str()); \
}
#define LOG_DEBUG(message) { \
    std::stringstream tempLogStream; tempLogStream << message; ::Log::instance.debug(tempLogStream.str()); \
}

#endif /* UTILS_LOG_HPP_ */
