#ifndef __SERIALIZER_HPP__
#define __SERIALIZER_HPP__

#include "Struct.hpp"
#include "Utils.hpp"

#include <fstream>
#include <sstream>

namespace JSONLib
{
	inline void WriteDictToFD(std::ostream &fd, const Dictionnary &dict, size_t offset = 0, bool colored = true)
	{
		using namespace Utils;
		const std::string indent(offset, ' ');

		if (dict.IsType<JSONObject>())
		{
			const JSONObject &obj = dict.As<JSONObject>();
			if (colored)
				fd << _BRACE_;
			fd << "{" << (colored ? _RESET_ : "") << (obj.size() != 0 ? "\n" : "");

			for (auto it = obj.begin(); it != obj.end(); ++it)
			{
				const auto &key = it->first;
				const auto &val = it->second;

				fd << std::string(offset + 4, ' ');
				if (colored)
					fd << _KEY_;
				fd << "\"" << key << "\"" << (colored ? _RESET_ : "");

				fd << (colored ? _COMMA_ : "") << ": " << (colored ? _RESET_ : "");

				WriteDictToFD(fd, val, offset + 4, colored);

				if (std::next(it) != obj.end())
					fd << (colored ? _COMMA_ : "") << "," << (colored ? _RESET_ : "");
				fd << std::endl;
			}

            if (obj.size() != 0)
			    fd << indent;
			if (colored)
				fd << _BRACE_;
			fd << "}" << (colored ? _RESET_ : "");
		}
		else if (dict.IsType<JSONVector>())
		{
			const JSONVector &vec = dict.As<JSONVector>();
			if (colored)
				fd << _BRACKET_;
			fd << "[" << (colored ? _RESET_ : "") << (vec.size() != 0 ? "\n" : "");

			for (size_t i = 0; i < vec.size(); ++i)
			{
				fd << std::string(offset + 4, ' ');
				WriteDictToFD(fd, vec[i], offset + 4, colored);
				if (i + 1 < vec.size())
					fd << (colored ? _COMMA_ : "") << "," << (colored ? _RESET_ : "");
				fd << std::endl;
			}

            if (vec.size() != 0)
			    fd << indent;
			if (colored)
				fd << _BRACKET_;
			fd << "]" << (colored ? _RESET_ : "");
		}
		else if (dict.IsType<std::nullptr_t>())
		{
			if (colored)
				fd << _NULL_;
			fd << "null" << (colored ? _RESET_ : "");
		}
		else if (dict.IsType<bool>())
		{
			if (colored)
				fd << (dict.As<bool>() ? _BOOL_TRUE_ : _BOOL_FALSE_);
			fd << (dict.As<bool>() ? "true" : "false") << (colored ? _RESET_ : "");
		}
		else if (dict.IsType<int>())
		{
			if (colored)
				fd << _INT_;
			fd << dict.As<int>() << (colored ? _RESET_ : "");
		}
		else if (dict.IsType<double>())
		{
			if (colored)
				fd << _DOUBLE_;
			fd << dict.As<double>() << (colored ? _RESET_ : "");
		}
		else if (dict.IsType<std::string>())
		{
			if (colored)
				fd << _STRING_;
			fd << "\"" << dict.As<std::string>() << "\"" << (colored ? _RESET_ : "");
		}
	}
	inline const std::string JSONToString(const Dictionnary &dict)
	{
		using namespace Utils;
        std::stringstream target;
        WriteDictToFD(target, dict, 0, false);
        return target.str();
	}
}; // namespace JSONLib

#endif // __SERIALIZER_HPP__