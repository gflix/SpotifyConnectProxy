#ifndef PROTOCOLS_STRINGLIST_HPP_
#define PROTOCOLS_STRINGLIST_HPP_

#include <models/ByteArray.hpp>
#include <models/StringList.hpp>

namespace Protocol
{

class StringList
{
public:
    static size_t fromLengthValueEncodedByteArray(
        const ::ByteArray& bytes,
        size_t offset,
        ::StringList& stringList);

    static ::ByteArray toLengthValueEncodedByteArray(const ::StringList& items);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_STRINGLIST_HPP_ */
