#ifndef MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDTXTPAYLOAD_HPP_
#define MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDTXTPAYLOAD_HPP_

#include <models/StringList.hpp>
#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

struct ResourceRecordTxtPayload: public GenericResourceRecordPayload
{
    explicit ResourceRecordTxtPayload(
        const StringList& lines = StringList());
    virtual ~ResourceRecordTxtPayload();

    StringList lines;

    std::string toString(void) const override;
};

#endif /* MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDTXTPAYLOAD_HPP_ */
