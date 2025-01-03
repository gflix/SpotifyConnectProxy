#ifndef UTILS_SPLIT_HPP_
#define UTILS_SPLIT_HPP_

#include <models/StringList.hpp>

class Split
{
public:
    static StringList string(
        std::string joinedString,
        const std::string& separator,
        bool trim = false,
        bool skipEmpty = true);
};

#endif /* UTILS_SPLIT_HPP_ */
