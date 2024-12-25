#include <sstream>
#include <models/GenericMdnsRecord.hpp>
#include <utils/Containers.hpp>
#include <utils/Join.hpp>

GenericMdnsRecord::GenericMdnsRecord(
    StringList name,
    DnsResourceType type,
    unsigned int classCode):
    name(name),
    type(type),
    classCode(classCode)
{
}

GenericMdnsRecord::~GenericMdnsRecord()
{
}

std::string GenericMdnsRecord::toString(void) const
{
    std::stringstream stream;
    char buffer[16];

    stream << "name=" << fullName() << ",";
    stream << "type=" << type << ",";
    snprintf(buffer, sizeof(buffer), "%04x", classCode);
    stream << "classCode=" << buffer;

    return stream.str();
}

std::string GenericMdnsRecord::fullName(void) const
{
    return Join::stringList(name, ".");
}
