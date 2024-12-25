#ifndef UTILS_CONTAINERS_HPP_
#define UTILS_CONTAINERS_HPP_

#include <ostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& entries)
{
    bool firstEntry = true;
    stream << "(";
    for (const auto& entry: entries) {
        if (firstEntry)
        {
            firstEntry = false;
        }
        else
        {
            stream << ",";
        }
        stream << entry;
    }
    stream << ")";
    return stream;
}

#endif /* UTILS_CONTAINERS_HPP_ */
