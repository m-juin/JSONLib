#ifndef __JSON_HPP__
#define __JSON_HPP__

#include "Parser.hpp"
#include "Serializer.hpp"
#include "Struct.hpp"

namespace JSONLib
{
	inline Dictionnary LoadJSON(const std::string &path)
	{
		std::ifstream opened(path, std::ifstream::in);
		if (opened.is_open() == false)
			throw std::runtime_error("File not found!");
		std::stringstream ss;
		ss << opened.rdbuf();
		auto dict = JSONLib::Parser::ParseToDict(ss.str());
		return dict;
	}

	inline void ExportToJSON(const Dictionnary &dict, const std::string &savePath)
	{
		std::ofstream os(savePath);
		WriteDictToFD(os, dict, 0, false);
        os << std::endl;
		os.close();
	}
} // namespace JSONLib

#endif // __JSON_HPP__