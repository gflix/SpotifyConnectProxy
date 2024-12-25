#ifndef PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDAPAYLOAD_HPP_
#define PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDAPAYLOAD_HPP_

#include <models/ByteArray.hpp>
#include <models/resource-record-payload/ResourceRecordAPayload.hpp>

namespace Protocol
{

class ResourceRecordAPayload
{
public:
    static ::ResourceRecordAPayload fromByteArray(
        const ::ByteArray& bytes,
        size_t offset,
        DnsResourceType type);
    static ::ByteArray toByteArray(const ::ResourceRecordAPayload& item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDAPAYLOAD_HPP_ */
