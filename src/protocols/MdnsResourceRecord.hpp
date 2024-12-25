#ifndef PROTOCOLS_MDNSRESOURCERECORD_HPP_
#define PROTOCOLS_MDNSRESOURCERECORD_HPP_

#include <models/ByteArray.hpp>
#include <models/MdnsResourceRecord.hpp>

namespace Protocol
{

class MdnsResourceRecord
{
public:
    static size_t fromByteArray(const ::ByteArray& bytes, size_t offset, ::MdnsResourceRecord& record);
    static ::ByteArray toByteArray(const ::MdnsResourceRecord& item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_MDNSRESOURCERECORD_HPP_ */
