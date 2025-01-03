#include <sstream>
#include <models/resource-record-payload/ResourceRecordAPayload.hpp>

ResourceRecordAPayload::ResourceRecordAPayload(
    const std::string& address):
    GenericResourceRecordPayload(DnsResourceType::A),
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
