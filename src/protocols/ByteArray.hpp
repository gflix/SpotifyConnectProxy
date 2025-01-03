#ifndef PROTOCOLS_BYTEARRAY_HPP_
#define PROTOCOLS_BYTEARRAY_HPP_

#include <models/ByteArray.hpp>

namespace Protocol
{

class ByteArray
{
public:
    static uint8_t decodeHexDigit(char digit);

    static ::ByteArray fromHex(const std::string& input);

    static std::string toHex(
        const ::ByteArray& data,
        const std::string& separator = std::string(),
        bool upperCase = false);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_BYTEARRAY_HPP_ */
