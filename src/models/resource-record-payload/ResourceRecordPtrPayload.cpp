#include <sstream>
#include <models/resource-record-payload/ResourceRecordPtrPayload.hpp>
#include <utils/Join.hpp>

ResourceRecordPtrPayload::ResourceRecordPtrPayload(
    DnsResourceType type,
    const StringList& domainName):
    GenericResourceRecordPayload(type),
    domainName(domainName)
{
}

ResourceRecordPtrPayload::~ResourceRecordPtrPayload()
{
}

std::string ResourceRecordPtrPayload::fullDomainName(void) const
{
    return Join::stringList(domainName, ".");
}

std::string ResourceRecordPtrPayload::toString(void) const
{
    std::stringstream stream;

    stream << "ResourceRecordPtrPayload[";
    stream << GenericResourceRecordPayload::toString() << ",";
    stream << "domainName=" << fullDomainName();
    stream << "]";

    return stream.str();
}
