#ifndef MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDAPAYLOAD_HPP_
#define MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDAPAYLOAD_HPP_

#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

struct ResourceRecordAPayload: public GenericResourceRecordPayload
{
    explicit ResourceRecordAPayload(
        const std::string& address = std::string());
    virtual ~ResourceRecordAPayload();

    std::string address;

    std::string toString(void) const override;
};

#endif /* MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDAPAYLOAD_HPP_ */
