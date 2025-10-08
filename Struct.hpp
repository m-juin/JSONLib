#ifndef __STRUCT_HPP__
#define __STRUCT_HPP__

#include <map>
#include <vector>
#include <string>
#include <variant>

namespace JSONLib
{
	struct Dictionnary;

	using JSONObject = std::map<std::string, Dictionnary>;
	using JSONVector = std::vector<Dictionnary>;

	struct Dictionnary
	{
		using Element = std::variant<int, double, std::string, JSONObject, JSONVector, std::nullptr_t>;
        Element content;

        Dictionnary() : content(nullptr) {}
        Dictionnary(nullptr_t) : content(nullptr) {}
        Dictionnary(const char *val) : content(std::string(val)) {}
        Dictionnary(const std::string &val) : content(val) {}
        Dictionnary(const bool &val) : content(int(val)) {}
        Dictionnary(const int &val) : content(val) {}
        Dictionnary(const float &val) : content(double(val)) {}
        Dictionnary(const double &val) : content(val) {}
        Dictionnary(const JSONObject &val) : content(std::move(val)) {}
        Dictionnary(const JSONVector &val) : content(std::move(val)) {}

        template <typename T>
        bool IsType() {return std::holds_alternative<T>(value)}

        
	};

} // namespace JSONLib

#endif // __STRUCT_HPP__