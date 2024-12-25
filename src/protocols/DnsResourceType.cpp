#include <stdexcept>
#include <protocols/DnsResourceType.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<std::string, ::DnsResourceType> identifierMapping {
    { "A", ::DnsResourceType::A },
    { "AAAA", ::DnsResourceType::AAAA },
    { "ANY", ::DnsResourceType::ANY },
    { "NSEC", ::DnsResourceType::NSEC },
    { "PTR", ::DnsResourceType::PTR },
    { "SRV", ::DnsResourceType::SRV },
    { "TXT", ::DnsResourceType::TXT },
};

const static std::map<unsigned int, ::DnsResourceType> codeMapping {
    { static_cast<int>(::DnsResourceType::A), ::DnsResourceType::A },
    { static_cast<int>(::DnsResourceType::AAAA), ::DnsResourceType::AAAA },
    { static_cast<int>(::DnsResourceType::ANY), ::DnsResourceType::ANY },
    { static_cast<int>(::DnsResourceType::NSEC), ::DnsResourceType::NSEC },
    { static_cast<int>(::DnsResourceType::PTR), ::DnsResourceType::PTR },
    { static_cast<int>(::DnsResourceType::SRV), ::DnsResourceType::SRV },
    { static_cast<int>(::DnsResourceType::TXT), ::DnsResourceType::TXT },
};

std::string DnsResourceType::toIdentifier(::DnsResourceType item)
{
    return EnumMapper<::DnsResourceType>::toIdentifierWithDefault(identifierMapping, item, "INVALID");
}

::DnsResourceType DnsResourceType::fromInteger(unsigned int value)
{
    auto it = codeMapping.find(value);
    if (it == codeMapping.cend())
    {
        throw std::invalid_argument("invalid query type \"" + std::to_string(value) + "\"");
    }

    return it->second;
}

} /* namespace Protocol */
