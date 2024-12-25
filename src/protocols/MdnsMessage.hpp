#ifndef PROTOCOLS_MDNSMESSAGE_HPP_
#define PROTOCOLS_MDNSMESSAGE_HPP_

#include <models/ByteArray.hpp>
#include <models/MdnsMessage.hpp>

namespace Protocol
{

class MdnsMessage
{
public:
    static ::MdnsMessage fromByteArray(const ::ByteArray& bytes);
    static ::ByteArray toByteArray(const ::MdnsMessage& item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_MDNSMESSAGE_HPP_ */
