#include <sstream>
#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

GenericResourceRecordPayload::GenericResourceRecordPayload(
    DnsResourceType type):
    type(type)
{
}

GenericResourceRecordPayload::~GenericResourceRecordPayload()
{
}

std::string GenericResourceRecordPayload::toString(void) const
{
    std::stringstream stream;

    stream << "type=" << type;

    return stream.str();
}

std::ostream& operator<<(std::ostream& stream, const GenericResourceRecordPayload& item)
{
    stream << item.toString();

    return stream;
}
