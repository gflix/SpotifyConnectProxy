#ifndef MODELS_MDNSQUERYRECORD_HPP_
#define MODELS_MDNSQUERYRECORD_HPP_

#include <ostream>
#include <vector>
#include <models/GenericMdnsRecord.hpp>

struct MdnsQueryRecord: public GenericMdnsRecord
{
    explicit MdnsQueryRecord(
        StringList name = StringList(),
        DnsResourceType type = DnsResourceType::INVALID,
        unsigned int classCode = 0,
        bool unicastResponse = false);
    virtual ~MdnsQueryRecord();

    bool unicastResponse;
};

typedef std::vector<MdnsQueryRecord> MdnsQueryRecords;

std::ostream& operator<<(std::ostream& stream, const MdnsQueryRecord& item);

#endif /* MODELS_MDNSQUERYRECORD_HPP_ */
