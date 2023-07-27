#pragma once

#include <string>
#include <regex>
#include <functional>

#include <glm/glm.hpp>

class IniReader
{
public:
    bool Read(std::string const &k, std::string const &v, bool &out);
    bool Read(std::string const &k, std::string const &v, int &out);
    bool Read(std::string const &k, std::string const &v, size_t &out);
    bool Read(std::string const &k, std::string const &v, float &out);
    bool Read(std::string const &k, std::string const &v, glm::vec3 &out);
    bool Read(std::string const &k, std::string const &v, std::string &out);
    bool Read(std::string const &k, std::string const &v, std::vector<int> &out);

private:
    static std::vector<std::string> Split(std::string srcStr, std::string delimStr,bool repeatedCharIgnored);
    static std::string Replace(std::string const& str, std::regex const& reg, std::function<std::string(std::sregex_iterator const&)> call, size_t offset = 0, size_t count = std::string::npos);
    static std::string Error(std::string const &k, std::string const &v);
};