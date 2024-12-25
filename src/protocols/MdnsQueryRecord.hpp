#ifndef PROTOCOLS_MDNSQUERYRECORD_HPP_
#define PROTOCOLS_MDNSQUERYRECORD_HPP_

#include <models/ByteArray.hpp>
#include <models/MdnsQueryRecord.hpp>

namespace Protocol
{

class MdnsQueryRecord
{
public:
    static size_t fromByteArray(const ::ByteArray& bytes, size_t offset, ::MdnsQueryRecord& record);
    static ::ByteArray toByteArray(const ::MdnsQueryRecord& item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_MDNSQUERYRECORD_HPP_ */
