#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <iostream>
#include <vector>

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

	inline std::vector<std::string> Split(const std::string &input)
	{
		std::vector<std::string> output;
		std::string toWork = Trim(input);
		size_t prevIndex = 0;
		size_t currentIndex = 0;
		while ((currentIndex = toWork.find_first_of("\n\0", prevIndex)) != toWork.npos)
		{
			std::string newOne = toWork.substr(prevIndex, currentIndex - prevIndex);
			newOne = Trim(newOne);
			if (newOne.empty() != true)
				output.push_back(newOne);
			prevIndex = currentIndex + 1;
		}
		if (currentIndex != prevIndex)
		{
			std::string newOne = toWork.substr(prevIndex);
			newOne = Trim(newOne);
			if (newOne.empty() != true)
				output.push_back(newOne);
		}
		return output;
	}

	enum TOKEN
	{
		LEFT_BRACE,
		RIGHT_BRACE,
		LEFT_BRACKET,
		RIGHT_BRACKET,
		COLON,
		COMMA,
		STRING,
		NUMBER,
		DOUBLE,
		TRUE,
		FALSE,
		NULL_TOK,
	};

	#ifndef __printColor__
	#define __printColor__
	#define _BOOL_TRUE_ "\033[1;92m"
	#define _BOOL_FALSE_ "\033[1;91m"
	#define _INT_ "\033[1;34m"
	#define _STRING_ "\033[1;35m"
	#define _KEY_ "\033[1;37m"
	#define _DOUBLE_ "\033[1;34m"
	#define _COMMA_ "\033[1;37m"
	#define _NULL_ "\033[1;35m"
	#define _BRACKET_ "\033[1;93m"
	#define _BRACE_ "\033[1;93m"
	#define _RESET_ "\033[0m"
	#endif 

} // namespace JSONLib::Utils

#endif // __UTILS_HPP__