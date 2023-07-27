#include <iostream>

#include "ini_reader.h"

bool IniReader::Read(std::string const &k, std::string const &v, bool &out)
{
    if (!v.empty())
    {
        out = atoi(v.c_str()) == 1;
        return true;
    }

    Error(k, v);
    return false;
}

bool IniReader::Read(std::string const &k, std::string const &v, int &out)
{
    if (!v.empty())
    {
        out = atoi(v.c_str());
        return true;
    }
    Error(k, v);
    return false;
}

bool IniReader::Read(std::string const &k, std::string const &v, size_t &out)
{
    if (!v.empty())
    {
        out = static_cast<size_t>(atoll(v.c_str()));
        return true;
    }

    Error(k, v);
    return false;
}


bool IniReader::Read(std::string const &k, std::string const &v, float &out)
{
    if (!v.empty())
    {
        out = atof(v.c_str());
        return true;
    }
    Error(k, v);
    return false;
}


bool IniReader::Read(std::string const &k, std::string const &v, glm::vec3 &out)
{
    auto tmp = Replace(v, std::regex("\\s*"), [](auto iter)
                       { return std::string(); });

    if (std::sscanf(tmp.c_str(), "%f,%f,%f", &out.x, &out.y, &out.z) == 3)
    {
        return true;
    }
    Error(k, v);
    return false;
}

bool IniReader::Read(std::string const &k, std::string const &v, std::string &out)
{
    if (!v.empty())
    {
        out = v;
        return true;
    }
    Error(k, v);
    return false;
}

bool IniReader::Read(std::string const &k, std::string const &v, std::vector<int> &out)
{
    if (!v.empty())
    {
        auto strs = Split(v,",",false);
        out.clear();
        std::transform(strs.begin(),strs.end(), std::back_inserter(out),[](auto s){return atoi(s.c_str());});
        return true;
    }
    Error(k, v);
    return false;
}


std::string IniReader::Replace(std::string const &str, std::regex const &reg, std::function<std::string(std::sregex_iterator const &)> call, size_t offset, size_t count)
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


std::vector<std::string> IniReader::Split(std::string srcStr, std::string delimStr,bool repeatedCharIgnored)
{
    std::vector<std::string> resultStringVector;
    std::replace_if(srcStr.begin(), srcStr.end(), [&](const char& c){if(delimStr.find(c)!=std::string::npos){return true;}else{return false;}}/*pred*/, delimStr.at(0));//将出现的所有分隔符都替换成为一个相同的字符（分隔符字符串的第一个）
    size_t pos=srcStr.find(delimStr.at(0));
    std::string addedString="";
    while (pos!=std::string::npos) {
        addedString=srcStr.substr(0,pos);
        if (!addedString.empty()||!repeatedCharIgnored) {
            resultStringVector.push_back(addedString);
        }
        srcStr.erase(srcStr.begin(), srcStr.begin()+pos+1);
        pos=srcStr.find(delimStr.at(0));
    }
    addedString=srcStr;
    if (!addedString.empty()||!repeatedCharIgnored) {
        resultStringVector.push_back(addedString);
    }
    return resultStringVector;

}

std::string IniReader::Error(std::string const &k, std::string const &v)
{
    auto msg = std::string("Invalid ini format: ") + k;
    std::cerr << msg << std::endl;
    return msg;
    //return std::string("Invalid ini format: ") + k;
    ///throw std::logic_error(std::string("Invalid ini format: ") + k);
}