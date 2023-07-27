#pragma once

#include <string>
#include <vector>
#include <functional>
#include <regex>


class StringUtil
{
public:
	static std::vector<std::string> Split(std::string const& str, char seperator);
	static std::vector<std::string> Split(std::string const& str, std::string const& separator);
	static std::string Join(std::vector<std::string> const& array, std::string const& str);
	static std::string Join(std::vector<std::string> const& array, std::string const& str, std::function<bool(std::string const&)> filter);
	static std::string Replace(std::string const& str, std::string const& substr, std::string const& newstr, size_t offset = 0, size_t count = std::string::npos);
	static std::string Replace(std::string const& str, std::regex const& reg, std::function<std::string(std::sregex_iterator const&)> call, size_t offset = 0, size_t count = std::string::npos);
};
