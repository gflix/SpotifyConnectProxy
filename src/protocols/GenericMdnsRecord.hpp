#ifndef PROTOCOLS_GENERICMDNSRECORD_HPP_
#define PROTOCOLS_GENERICMDNSRECORD_HPP_

#include <models/ByteArray.hpp>
#include <models/GenericMdnsRecord.hpp>

namespace Protocol
{

class GenericMdnsRecord
{
public:
    static size_t fromByteArray(const ::ByteArray& bytes, size_t offset, ::GenericMdnsRecord& record);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_GENERICMDNSRECORD_HPP_ */
