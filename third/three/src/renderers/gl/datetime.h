#pragma once

#include <chrono>
#include <sstream>

using namespace std;

namespace three::gl
{

  class Datetime
  {
  public:
    static int64_t GetTimeUS();

    static int64_t GetLocalTimeMS();

    static string GMTime2LocalStr(int64_t time_us, const string& fmt = "%Y-%m-%d %H:%M:%S");

    static int64_t LocalStr2GMTime(const std::string& s, const std::string& fmt = "%Y-%m-%d %H:%M:%S");

    static std::string Time2Str(int64_t time_us, const std::string& fmt = "%Y-%m-%d %H:%M:%S");

    static int64_t Str2Time(const std::string& s, const std::string& fmt = "%Y-%m-%d %H:%M:%S");
  };
}
