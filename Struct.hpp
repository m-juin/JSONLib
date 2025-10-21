#ifndef __STRUCT_HPP__
#define __STRUCT_HPP__

#include <cstddef>
#include <map>
#include <string>
#include <variant>
#include <vector>

#include <iostream>

namespace JSONLib
{
	struct Dictionnary;

	using JSONObject = std::map<std::string, Dictionnary>;
	using JSONVector = std::vector<Dictionnary>;

	struct Dictionnary
	{
			using Element = std::variant<int, double, bool, std::string, JSONObject, JSONVector, std::nullptr_t>;
			Element content;

			Dictionnary() : content(nullptr) {}
			Dictionnary(std::nullptr_t) : content(nullptr) {}
			Dictionnary(const char *val) : content(std::string(val)) {}
			Dictionnary(const std::string &val) : content(val) {}
			Dictionnary(const bool &val) : content(val) {}
			Dictionnary(const int &val) : content(val) {}
			Dictionnary(const float &val) : content(double(val)) {}
			Dictionnary(const double &val) : content(val) {}
			Dictionnary(const JSONObject &val) : content(std::move(val)) {}
			Dictionnary(const JSONVector &val) : content(std::move(val)) {}

			template <typename T> bool IsType() const
			{
				return std::holds_alternative<T>(content);
			}

			// const Dictionnary &operator[](const std::string &key)
			// {
			// 	if (this->IsType<JSONObject>() == false)
			// 		auto content = JSONObject{};
			// 	return std::get<JSONObject>(content)[key];
			// }

			Dictionnary &operator[](const std::string &key)
			{
				std::cout << "here\n";
				if (this->IsType<JSONObject>() == false)
					content = JSONObject{};
				return std::get<JSONObject>(content)[key];
			}

			Dictionnary &operator[](const size_t &index)
			{
				if (this->IsType<JSONVector>() == false)
					content = JSONVector{};
				auto &vec = std::get<JSONVector>(content);
				if (index >= vec.size())
					vec.resize(index + 1);
				return vec[index];
			}

			bool operator==(const Dictionnary &other) const noexcept
			{
				return content == other.content;
			}
			bool operator!=(const Dictionnary &other) const noexcept
			{
				return !(*this == other);
			}

			template <typename T> const T &As() const
			{
				return std::get<T>(content);
			};

			template <typename T> T &As()
			{
				return std::get<T>(content);
			};

			// std::ostream &operator<<(std::ostream &os, const JSONVector &vec)
			// {
			//     os <<
			// }
	};
} // namespace JSONLib

#endif // __STRUCT_HPP__