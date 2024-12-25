#include <protocols/DnsMessageType.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<std::string, ::DnsMessageType> mapping {
    { "QUERY", ::DnsMessageType::QUERY },
    { "REPLY", ::DnsMessageType::REPLY },
};

std::string DnsMessageType::toIdentifier(::DnsMessageType item)
{
    return EnumMapper<::DnsMessageType>::toIdentifierWithDefault(mapping, item, "INVALID");
}

} /* namespace Protocol */
