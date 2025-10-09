#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "Struct.hpp"

namespace JSONLib::Parser
{
    inline Dictionnary ParseToDict(const std::string &input)
    {
        Dictionnary rootObject;
        (void)input;
        return rootObject;
    }
} // namespace JSONLib::Parser


#endif // __PARSER_HPP__