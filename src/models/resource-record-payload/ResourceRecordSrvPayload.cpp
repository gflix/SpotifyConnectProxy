#include <sstream>
#include <models/resource-record-payload/ResourceRecordSrvPayload.hpp>
#include <utils/Join.hpp>

ResourceRecordSrvPayload::ResourceRecordSrvPayload(
    unsigned int priority,
    unsigned int weight,
    unsigned int port,
    const StringList& target):
    GenericResourceRecordPayload(DnsResourceType::SRV),
    priority(priority),
    weight(weight),
    port(port),
    target(target)
{
}

ResourceRecordSrvPayload::~ResourceRecordSrvPayload()
{
}

std::string ResourceRecordSrvPayload::fullTarget(void) const
{
    return Join::stringList(target, ".");
}

std::string ResourceRecordSrvPayload::toString(void) const
{
    std::stringstream stream;

    stream << "ResourceRecordSrvPayload[";
    stream << GenericResourceRecordPayload::toString() << ",";
    stream << "priority=" << priority << ",";
    stream << "weight=" << weight << ",";
    stream << "port=" << port << ",";
    stream << "target=" << fullTarget();
    stream << "]";

    return stream.str();
}
