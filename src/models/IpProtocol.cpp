#include <protocols/IpProtocol.hpp>

std::ostream& operator<<(std::ostream& stream, const IpProtocol& item)
{
    stream << Protocol::IpProtocol::toIdentifier(item);

    return stream;
}
