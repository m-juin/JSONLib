#include "../Utils.hpp"

#include <functional>

#include <vector>

std::vector<std::function<void()>> tests = {
	[]()
	{
		std::string sol = "    { toto } \t \t    ";
		std::string result = JSONLib::Utils::Trim(sol);
		std::cout << result << std::endl;
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
			std::cerr << e.what() << '\n';
		}
	}
}