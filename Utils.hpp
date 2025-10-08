#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <iostream>

namespace JSONLib::Utils
{
    inline std::string Trim(const std::string &original, const char *toTrim = " \t")
    {
        size_t firstPos = original.find_first_not_of(toTrim);
        size_t secondPos = original.find_last_not_of(toTrim) + 1;

        if (firstPos >= secondPos)
            return "";
        return original.substr(firstPos, secondPos - firstPos);
    }
}

#endif // __UTILS_HPP__ 