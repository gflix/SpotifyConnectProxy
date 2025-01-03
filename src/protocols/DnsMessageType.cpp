#include <protocols/DnsMessageType.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<::DnsMessageType, std::string> mapping {
    { ::DnsMessageType::QUERY, "QUERY" },
    { ::DnsMessageType::REPLY, "REPLY" },
};

std::string DnsMessageType::toIdentifier(::DnsMessageType item)
{
    return EnumMapper<::DnsMessageType>::toIdentifierWithDefault(mapping, item, "INVALID");
}

} /* namespace Protocol */
