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
		// std::cout << "input = " << input << std::endl;
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
} // namespace JSONLib::Utils

#endif // __UTILS_HPP__