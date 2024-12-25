#include <protocols/DnsMessageType.hpp>

std::ostream& operator<<(std::ostream& stream, const DnsMessageType& item)
{
    stream << Protocol::DnsMessageType::toIdentifier(item);

    return stream;
}
