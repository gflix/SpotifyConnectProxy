#include <protocols/LogLevel.hpp>

std::ostream& operator<<(std::ostream& stream, const LogLevel& item)
{
    stream << Protocol::LogLevel::toIdentifier(item);

    return stream;
}
