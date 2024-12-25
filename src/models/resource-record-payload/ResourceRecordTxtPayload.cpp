#include <sstream>
#include <models/resource-record-payload/ResourceRecordTxtPayload.hpp>
#include <utils/Containers.hpp>

ResourceRecordTxtPayload::ResourceRecordTxtPayload(
    DnsResourceType type,
    const StringList& lines):
    GenericResourceRecordPayload(type),
    lines(lines)
{
}

ResourceRecordTxtPayload::~ResourceRecordTxtPayload()
{
}

std::string ResourceRecordTxtPayload::toString(void) const
{
    std::stringstream stream;

    stream << "ResourceRecordTxtPayload[";
    stream << GenericResourceRecordPayload::toString() << ",";
    stream << "lines=" << lines;
    stream << "]";

    return stream.str();
}
