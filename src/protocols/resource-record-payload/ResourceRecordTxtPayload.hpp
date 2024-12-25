#ifndef PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDTXTPAYLOAD_HPP_
#define PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDTXTPAYLOAD_HPP_

#include <models/ByteArray.hpp>
#include <models/resource-record-payload/ResourceRecordTxtPayload.hpp>

namespace Protocol
{

class ResourceRecordTxtPayload
{
public:
    static ::ResourceRecordTxtPayload fromByteArray(
        const ::ByteArray& bytes,
        size_t offset,
        ssize_t length,
        DnsResourceType type);
    static ::ByteArray toByteArray(const ::ResourceRecordTxtPayload& item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDTXTPAYLOAD_HPP_ */
