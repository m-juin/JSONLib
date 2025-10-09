#include "../Utils.hpp"
#include "../Json.hpp"

#include <functional>

#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::function<void()>> tests = {
	[]()
	{
		std::string sol = "    { toto } \t \t    ";
		std::string result = JSONLib::Utils::Trim(sol);
		std::cout << result << std::endl;
	},
	[]()
	{
		std::string sol = "";
		std::string result = JSONLib::Utils::Trim(sol);
		std::cout << result << std::endl;
	},
	[]()
	{
		std::string sol = "\t ";
		std::string result = JSONLib::Utils::Trim(sol);
		std::cout << result << std::endl;
	},
	[]()
	{
		JSONLib::Dictionnary dict;
		dict[0] = 5;
		dict[1]["toto"] = "tata";
		std::cout << std::boolalpha << "isInt = " << dict.IsType<int>() << " | isDouble = " << dict.IsType<double>() << " | isString = " << dict.IsType<std::string>() << " | isObject = " << dict.IsType<JSONLib::JSONObject>() << " | isVector = " << dict.IsType<JSONLib::JSONVector>() << std::endl;
		std::cout << "Dict[0] = " << dict[0].As<int>() << std::endl;
		std::cout << "Dict[1] = " << std::boolalpha << "isInt = " << dict[1].IsType<int>() << " | isDouble = " << dict[1].IsType<double>() << " | isString = " << dict[1].IsType<std::string>() << " | isObject = " << dict[1].IsType<JSONLib::JSONObject>() << " | isVector = " << dict[1].IsType<JSONLib::JSONVector>() << std::endl;
	},
	[]()
	{
		const std::string path = "./Test/simple.json";
		std::ifstream opened(path, std::ifstream::in);
		if (opened.is_open() == false)
			throw std::runtime_error("File not found!");
		std::stringstream ss;
		ss << opened.rdbuf();
		std::vector<std::string> result = JSONLib::Utils::Split(ss.str());
		for (const std::string &line : result)
			std::cout << line << std::endl;
	},
};

int main(int ac, char *av[])
{
	std::vector<size_t> testIndexs;
	if (ac != 1)
	{
		testIndexs.resize(ac - 1);
		for (size_t count = 1; count < (size_t)ac; count++)
			testIndexs[count - 1] = std::atoi(av[count]);
	}
	else
		testIndexs.push_back(0);

	for (size_t index : testIndexs)
	{
		try
		{
			if (index >= tests.size())
				throw std::runtime_error("Invalid Test index");
			tests[index]();
		}
		catch (const std::exception &e)
		{
			std::cerr << "\033[1;31m" << "[ERROR] " << e.what() << "\033[0m" << '\n';
		}
	}
}