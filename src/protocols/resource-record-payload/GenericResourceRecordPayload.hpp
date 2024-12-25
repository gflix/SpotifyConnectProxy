#ifndef PROTOCOLS_RESOURCE_RECORD_PAYLOAD_GENERICRESOURCERECORDPAYLOAD_HPP_
#define PROTOCOLS_RESOURCE_RECORD_PAYLOAD_GENERICRESOURCERECORDPAYLOAD_HPP_

#include <models/ByteArray.hpp>
#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

namespace Protocol
{

class GenericResourceRecordPayload
{
public:
    static ::GenericResourceRecordPayload* fromByteArray(
        const ::ByteArray& bytes,
        size_t offset,
        ssize_t length,
        DnsResourceType type);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_RESOURCE_RECORD_PAYLOAD_GENERICRESOURCERECORDPAYLOAD_HPP_ */
