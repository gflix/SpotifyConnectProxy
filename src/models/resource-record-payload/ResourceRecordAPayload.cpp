#include <sstream>
#include <models/resource-record-payload/ResourceRecordAPayload.hpp>

ResourceRecordAPayload::ResourceRecordAPayload(
    DnsResourceType type,
    const std::string& address):
    GenericResourceRecordPayload(type),
    address(address)
{
}

ResourceRecordAPayload::~ResourceRecordAPayload()
{
}

std::string ResourceRecordAPayload::toString(void) const
{
    std::stringstream stream;

    stream << "ResourceRecordAPayload[";
    stream << GenericResourceRecordPayload::toString() << ",";
    stream << "address=" << address;
    stream << "]";

    return stream.str();
}
