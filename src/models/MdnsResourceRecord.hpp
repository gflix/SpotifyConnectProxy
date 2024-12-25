#ifndef MODELS_MDNSRESOURCERECORD_HPP_
#define MODELS_MDNSRESOURCERECORD_HPP_

#include <memory>
#include <ostream>
#include <vector>
#include <models/ByteArray.hpp>
#include <models/GenericMdnsRecord.hpp>
#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

struct MdnsResourceRecord: public GenericMdnsRecord
{
    explicit MdnsResourceRecord(
        StringList name = StringList(),
        DnsResourceType type = DnsResourceType::INVALID,
        unsigned int classCode = 0,
        bool cacheFlush = false,
        unsigned int timeToLive = 0,
        ByteArray data = ByteArray());
    MdnsResourceRecord(MdnsResourceRecord&&) = default;
    virtual ~MdnsResourceRecord();

    bool cacheFlush;
    unsigned int timeToLive;
    ByteArray data;
    std::unique_ptr<GenericResourceRecordPayload> decodedData;
};

typedef std::vector<MdnsResourceRecord> MdnsResourceRecords;

std::ostream& operator<<(std::ostream& stream, const MdnsResourceRecord& item);

#endif /* MODELS_MDNSRESOURCERECORD_HPP_ */
