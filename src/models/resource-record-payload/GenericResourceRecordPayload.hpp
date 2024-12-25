#ifndef MODELS_RESOURCE_RECORD_PAYLOAD_GENERICRESOURCERECORDPAYLOAD_HPP_
#define MODELS_RESOURCE_RECORD_PAYLOAD_GENERICRESOURCERECORDPAYLOAD_HPP_

#include <ostream>
#include <models/DnsResourceType.hpp>

struct GenericResourceRecordPayload
{
    explicit GenericResourceRecordPayload(DnsResourceType type);
    virtual ~GenericResourceRecordPayload();

    DnsResourceType type;

    virtual std::string toString(void) const;
};

std::ostream& operator<<(std::ostream& stream, const GenericResourceRecordPayload& item);

#endif /* MODELS_RESOURCE_RECORD_PAYLOAD_GENERICRESOURCERECORDPAYLOAD_HPP_ */
