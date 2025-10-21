#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "Struct.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <cstring>

namespace JSONLib::Parser
{

	using LexerToken = std::pair<Utils::TOKEN, const std::string>;
	using LexerArray = std::vector<LexerToken>;

	JSONLib::Parser::LexerArray BuildLexer(const std::string &input)
	{
		LexerArray tree;
		size_t len = input.length();
		const char *charred = input.c_str();
		size_t next = 0;

		for (size_t index = 0; index < len;)
		{
			const char current = input[index];
			switch (current)
			{
			case '{':
				tree.push_back({Utils::TOKEN::LEFT_BRACE, "{"});
				index++;
				break;
			case '}':
				tree.push_back({Utils::TOKEN::RIGHT_BRACE, "}"});
				index++;
				break;
			case '[':
				tree.push_back({Utils::TOKEN::LEFT_BRACKET, "["});
				index++;
				break;
			case ']':
				tree.push_back({Utils::TOKEN::RIGHT_BRACKET, "]"});
				index++;
				break;
			case ':':
				tree.push_back({Utils::TOKEN::COLON, ":"});
				index++;
				break;
			case ',':
				tree.push_back({Utils::TOKEN::COMMA, ","});
				index++;
				break;
			case '"':
			{
				std::string buffer;
				index++;
				while (index < len)
				{
					char c = input[index];
					if (c == '\\' && index + 1 < len)
					{
						buffer += input[index + 1];
						index += 2;
					}
					else if (c == '"')
						break;
					else
					{
						buffer += c;
						index++;
					}
				}
				tree.push_back({Utils::TOKEN::STRING, buffer});
				index++;
				break;
			}

			default:
				if (isspace(current))
				{
					index++;
					break;
				}

				if (isdigit(current) || current == '-')
				{
					bool dotConsumed = false;
					next = index + 1;
					while (next < len && (isdigit(input[next]) || (!dotConsumed && input[next] == '.')))
					{
						if (input[next] == '.')
							dotConsumed = true;
						next++;
					}
					tree.push_back(
						{dotConsumed ? Utils::TOKEN::DOUBLE : Utils::TOKEN::NUMBER, input.substr(index, next - index)});
					index = next;
					break;
				}

				if (index + 4 <= len && strncmp(&charred[index], "true", 4) == 0)
				{
					tree.push_back({Utils::TOKEN::TRUE, "true"});
					index += 4;
					break;
				}
				if (index + 5 <= len && strncmp(&charred[index], "false", 5) == 0)
				{
					tree.push_back({Utils::TOKEN::FALSE, "false"});
					index += 5;
					break;
				}
				if (index + 4 <= len && strncmp(&charred[index], "null", 4) == 0)
				{
					tree.push_back({Utils::TOKEN::NULL_TOK, "null"});
					index += 4;
					break;
				}

				std::cerr << "Unknown character at index " << index << ": '" << current << "'" << std::endl;
				index++;
				break;
			}
		}

		return tree;
	}

	static std::pair<Dictionnary, size_t> BuildElement(JSONLib::Parser::LexerArray &array, size_t pos);

	static std::pair<std::pair<std::string, Dictionnary>, size_t> GetNextObjectElem(LexerArray &array, size_t pos)
	{
		std::pair<std::string, Dictionnary> pair;
		if (array.size() <= pos + 2)
			throw std::runtime_error("Error");
		else if (array[pos].first != Utils::TOKEN::STRING || array[pos + 1].first != Utils::TOKEN::COLON)
			throw std::runtime_error("Error");
		pair.first = array[pos].second;
		auto pair2 = BuildElement(array, pos + 2);
		pair.second = pair2.first;
		return {pair, pair2.second};
	}

	// static std::pair<Dictionnary, size_t> GetNextVectorElem(LexerArray &array, size_t pos)
	// {
	//     Dictionnary dict;
	//     if (array.size() <= pos)
	//         throw std::runtime_error("Error");
	//     dict = BuildElement(array, pos + 1);
	//     return dict;
	// }

	static std::pair<Dictionnary, size_t> BuildElement(LexerArray &array, size_t pos)
	{
		if (pos >= array.size())
			return {Dictionnary(nullptr), pos};

		const auto &token = array[pos];

		switch (token.first)
		{
		case Utils::TOKEN::STRING:
			return {Dictionnary(token.second), pos + 1};

		case Utils::TOKEN::NUMBER:
			return {Dictionnary(std::stoi(token.second)), pos + 1};

		case Utils::TOKEN::DOUBLE:
			return {Dictionnary(std::stod(token.second)), pos + 1};

		case Utils::TOKEN::TRUE:
			return {Dictionnary(true), pos + 1};

		case Utils::TOKEN::FALSE:
			return {Dictionnary(false), pos + 1};

		case Utils::TOKEN::NULL_TOK:
			return {Dictionnary(nullptr), pos + 1};

		case Utils::TOKEN::LEFT_BRACE:
		{
			JSONObject obj;
			pos++;

			while (pos < array.size() && array[pos].first != Utils::TOKEN::RIGHT_BRACE)
			{
				auto pair = GetNextObjectElem(array, pos);
				obj[pair.first.first] = pair.first.second;
				pos = pair.second;

				if (pos < array.size() && array[pos].first == Utils::TOKEN::COMMA)
					pos++;
			}

			if (pos >= array.size() || array[pos].first != Utils::TOKEN::RIGHT_BRACE)
				throw std::runtime_error("Unclosed object");

			return {Dictionnary(obj), pos + 1};
		}

		case Utils::TOKEN::LEFT_BRACKET:
		{
			JSONVector vec;
			pos++;

			while (pos < array.size() && array[pos].first != Utils::TOKEN::RIGHT_BRACKET)
			{
				auto pair = BuildElement(array, pos);
				vec.push_back(pair.first);
				pos = pair.second;

				if (pos < array.size() && array[pos].first == Utils::TOKEN::COMMA)
					pos++;
			}

			if (pos >= array.size() || array[pos].first != Utils::TOKEN::RIGHT_BRACKET)
				throw std::runtime_error("Unclosed array");

			return {Dictionnary(vec), pos + 1};
		}

		default:
			throw std::runtime_error("Unexpected token in JSON");
		}
	}

	inline Dictionnary ParseToDict(const std::string &input)
	{
		auto array = BuildLexer(input);
		return BuildElement(array, size_t(0)).first;
	}

	// static bool isJsonContainer(const std::string &line, const char elem)
	// {
	// 	size_t start = 0;
	// 	size_t pos = 0;

	// 	if ((pos = line.find(':')) != line.npos)
	// 		start = pos + 1;
	// 	// std::cout << line.substr(start, line.length() - start)[0] << std::endl;
	// 	if (Utils::Trim(line.substr(start, line.length() - start))[0] == elem)
	// 		return true;
	// 	return false;
	// }

	// inline void IsValid(std::vector<std::string> &&lines)
	// {
	// 	int mapOpenCount = std::count_if(lines.begin(), lines.end(),
	// 								 [](const std::string &line) { return isJsonContainer(line, '{'); });
	// 	int mapCloseCount = std::count_if(lines.begin(), lines.end(),
	// 							  [](const std::string &line) { return isJsonContainer(line, '}'); });
	//     std::cout << "MAP : " << mapOpenCount << " | " << mapCloseCount << std::endl;
	// 	if (mapOpenCount - mapCloseCount != 0)
	// 		throw std::runtime_error("Invalid JSON File.");
	// 	int arrayOpenCount = std::count_if(lines.begin(), lines.end(),
	// 							 [](const std::string &line) { return isJsonContainer(line, '['); });
	// 	int arrayCloseCount = std::count_if(lines.begin(), lines.end(),
	// 							  [](const std::string &line) { return isJsonContainer(line, ']'); });
	//     std::cout << "Array : " << arrayOpenCount << " | " << arrayCloseCount << std::endl;
	// 	if (arrayOpenCount - arrayCloseCount != 0)
	// 		throw std::runtime_error("Invalid JSON File.");
	// 	std::cout << "Valid JSON File" << std::endl;
	// 	// size_t arrayCount = 0;
	// }

} // namespace JSONLib::Parser

#endif // __PARSER_HPP__