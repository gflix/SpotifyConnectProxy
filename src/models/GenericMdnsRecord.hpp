#ifndef MODELS_GENERICMDNSRECORD_HPP_
#define MODELS_GENERICMDNSRECORD_HPP_

#include <string>
#include <models/DnsResourceType.hpp>
#include <models/StringList.hpp>

struct GenericMdnsRecord
{
    explicit GenericMdnsRecord(
        StringList name = StringList(),
        DnsResourceType type = DnsResourceType::INVALID,
        unsigned int classCode = 0);
    virtual ~GenericMdnsRecord();

    StringList name;
    DnsResourceType type;
    unsigned int classCode;

    std::string toString(void) const;
    std::string fullName(void) const;
};

#endif /* MODELS_GENERICMDNSRECORD_HPP_ */
