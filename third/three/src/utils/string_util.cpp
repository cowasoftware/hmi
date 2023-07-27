#include <iostream>
#include <sstream>

#include "string_util.h"

std::vector<std::string> StringUtil::Split(std::string const& str, std::string const& separator)
{
	std::vector<std::string> result;

	if (str.empty())
	{
		return result;
	}

	std::string temp = str + separator;
	size_t pos = temp.find(separator);
	int step = separator.size();

	while (pos != temp.npos)
	{
		std::string temp2 = temp.substr(0, pos);
		result.push_back(temp2);
		temp = temp.substr(pos + step, temp.size());
		pos = temp.find(separator);
	}

	return result;
}

std::vector<std::string> StringUtil::Split(std::string const& str, char separator)
{
	std::vector<std::string> result;

	if (str.empty())
	{
		return result;
	}

	std::stringstream iss(str);
	std::string temp;
	while (getline(iss, temp, separator))
	{
		result.emplace_back(temp);
	}

	return result;
}

std::string StringUtil::Join(std::vector<std::string> const& array, std::string const& str)
{
	std::stringstream ss;
	std::string result;

	for (auto& item : array)
	{
		ss << item << str;
	}

	result = ss.str();

	if (result.rfind(str) + str.size() == result.size() && !result.empty())
	{
		result.erase(result.end() - str.size());
	}

	return result;
}

std::string StringUtil::Join(std::vector<std::string> const& array, std::string const& str, std::function<bool(std::string const&)> filter)
{
	std::stringstream ss;
	std::string result;

	if (!filter)
	{
		throw std::invalid_argument("std::StringUtil.Join: Invalid Filter");
	}

	for (auto& item : array)
	{
		if (filter(item))
		{
			ss << item << str;
		}
	}

	result = ss.str();

	if (result.rfind(str) + str.size() == result.size() && !result.empty())
	{
		result.erase(result.end() - str.size());
	}

	return result;
}

std::string StringUtil::Replace(std::string const& str, std::string const& substr, std::string const& newstr, size_t offset, size_t count)
{
	std::stringstream ss;
	size_t index = 0;
	size_t cursor = 0;
	size_t position = 0;

	if (offset < str.size())
	{
		ss << str.substr(cursor, offset);
		cursor += offset;

		while ((position = str.find(substr, cursor)) != std::string::npos && index++ < count)
		{
			ss << str.substr(cursor, position - cursor) << newstr;
			cursor = position + substr.size();
		}

		ss << str.substr(cursor);
	}

	return ss.str();
}

std::string StringUtil::Replace(std::string const& str, std::regex const& reg, std::function<std::string(std::sregex_iterator const&)> call, size_t offset, size_t count)
{
	std::stringstream ss;
	size_t cursor = 0;
	size_t index = 0;
	std::string newstr;
	std::smatch match;

	if (offset < str.size())
	{
		ss << str.substr(cursor, offset);
		cursor += offset;

		for (std::sregex_iterator iter(str.begin() + offset, str.end(), reg), iter_end; iter != iter_end; iter++)
		{
			if (index++ >= count)
			{
				break;
			}
			ss << str.substr(cursor, iter->position() + offset - cursor) << call(iter);
			cursor = offset + iter->position() + iter->length();
		}
		ss << str.substr(cursor);
	}
	return ss.str();
}
