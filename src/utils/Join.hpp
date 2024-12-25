#ifndef UTILS_JOIN_HPP_
#define UTILS_JOIN_HPP_

#include <models/StringList.hpp>

class Join
{
public:
    static std::string stringList(const StringList& items, const std::string delimiter = std::string());
};

#endif /* UTILS_JOIN_HPP_ */
