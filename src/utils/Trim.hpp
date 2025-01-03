#ifndef UTILS_TRIM_HPP_
#define UTILS_TRIM_HPP_

#include <string>

class Trim
{
public:
    static std::string left(const std::string& text);
    static std::string right(const std::string& text);
    static std::string both(const std::string& text);
};

#endif /* UTILS_TRIM_HPP_ */
