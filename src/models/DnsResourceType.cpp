#include <protocols/DnsResourceType.hpp>

std::ostream& operator<<(std::ostream& stream, const DnsResourceType& item)
{
    stream << Protocol::DnsResourceType::toIdentifier(item);

    return stream;
}
