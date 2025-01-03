#include <stdexcept>
#include <protocols/DnsResourceType.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<::DnsResourceType, std::string> identifierMapping {
    { ::DnsResourceType::A, "A" },
    { ::DnsResourceType::AAAA, "AAAA" },
    { ::DnsResourceType::ANY, "ANY" },
    { ::DnsResourceType::NSEC, "NSEC" },
    { ::DnsResourceType::PTR, "PTR" },
    { ::DnsResourceType::SRV, "SRV" },
    { ::DnsResourceType::TXT, "TXT" },
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
        throw std::out_of_range("invalid query type \"" + std::to_string(value) + "\"");
    }

    return it->second;
}

} /* namespace Protocol */
