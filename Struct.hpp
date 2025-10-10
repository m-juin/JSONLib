#ifndef __STRUCT_HPP__
#define __STRUCT_HPP__

#include <cstddef>
#include <map>
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

			void Print(size_t offset = 0, bool colored = true) const
			{
				using namespace Utils;
				const std::string indent(offset, ' ');

				if (this->IsType<JSONObject>())
				{
					const JSONObject &obj = this->As<JSONObject>();
					if (colored)
						std::cout << _BRACE_;
					std::cout << "{" << (colored ? _RESET_ : "") << std::endl;

					for (auto it = obj.begin(); it != obj.end(); ++it)
					{
						const auto &key = it->first;
						const auto &val = it->second;

						std::cout << std::string(offset + 4, ' ');
						if (colored)
							std::cout << _KEY_;
						std::cout << "\"" << key << "\"" << (colored ? _RESET_ : "");

						std::cout << (colored ? _COMMA_ : "") << " : " << (colored ? _RESET_ : "");

						val.Print(offset + 4, colored);

						if (std::next(it) != obj.end())
							std::cout << (colored ? _COMMA_ : "") << "," << (colored ? _RESET_ : "");
						std::cout << std::endl;
					}

					std::cout << indent;
					if (colored)
						std::cout << _BRACE_;
					std::cout << "}" << (colored ? _RESET_ : "");
				}
				else if (this->IsType<JSONVector>())
				{
					const JSONVector &vec = this->As<JSONVector>();
					if (colored)
						std::cout << _BRACKET_;
					std::cout << "[" << (colored ? _RESET_ : "") << std::endl;

					for (size_t i = 0; i < vec.size(); ++i)
					{
						std::cout << std::string(offset + 4, ' ');
						vec[i].Print(offset + 4, colored);
						if (i + 1 < vec.size())
							std::cout << (colored ? _COMMA_ : "") << "," << (colored ? _RESET_ : "");
						std::cout << std::endl;
					}

					std::cout << indent;
					if (colored)
						std::cout << _BRACKET_;
					std::cout << "]" << (colored ? _RESET_ : "");
				}
				else if (this->IsType<std::nullptr_t>())
				{
					if (colored)
						std::cout << _NULL_;
					std::cout << "null" << (colored ? _RESET_ : "");
				}
				else if (this->IsType<bool>())
				{
					if (colored)
						std::cout << (this->As<bool>() ? _BOOL_TRUE_ : _BOOL_FALSE_);
					std::cout << (this->As<bool>() ? "true" : "false") << (colored ? _RESET_ : "");
				}
				else if (this->IsType<int>())
				{
					if (colored)
						std::cout << _INT_;
					std::cout << this->As<int>() << (colored ? _RESET_ : "");
				}
				else if (this->IsType<double>())
				{
					if (colored)
						std::cout << _DOUBLE_;
					std::cout << this->As<double>() << (colored ? _RESET_ : "");
				}
				else if (this->IsType<std::string>())
				{
					if (colored)
						std::cout << _STRING_;
					std::cout << "\"" << this->As<std::string>() << "\"" << (colored ? _RESET_ : "");
				}
			}
	};

	// std::ostream &operator<<(std::ostream &os, const JSONVector &vec)
	// {
	//     os <<
	// }

} // namespace JSONLib

#endif // __STRUCT_HPP__