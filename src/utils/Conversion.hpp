#ifndef UTILS_CONVERSION_HPP_
#define UTILS_CONVERSION_HPP_

#include <models/ByteArray.hpp>

class Conversion
{
public:
    static uint16_t uint16FromByteArray(const ::ByteArray& bytes);
    static uint32_t uint32FromByteArray(const ::ByteArray& bytes);

    static ::ByteArray uint16ToByteArray(uint16_t value);
    static ::ByteArray uint32ToByteArray(uint32_t value);
};

#endif /* UTILS_CONVERSION_HPP_ */
