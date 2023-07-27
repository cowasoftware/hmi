#include <iomanip>

#include "./datetime.h"

namespace three::gl
{
  static constexpr int64_t SEC = 1000000;
  static constexpr int64_t MIN = SEC * 60;
  static constexpr int64_t HOUR = MIN * 60;
  static constexpr int64_t DAY = HOUR * 24;

  int64_t Datetime::GetTimeUS()
  {
    chrono::system_clock clock;
    return chrono::duration_cast<chrono::microseconds>(
               clock.now().time_since_epoch())
        .count();
  }

  int64_t Datetime::GetLocalTimeMS()
  {
    return GetTimeUS() + HOUR * 8;
  }


  string Datetime::GMTime2LocalStr(int64_t time_us, const string &fmt)
  {
    stringstream ss;
    time_t t = time_us / SEC;
    auto tm = std::localtime(&t);

    ss << std::put_time(tm, fmt.c_str());
    return ss.str();
  }


  int64_t Datetime::LocalStr2GMTime(const std::string &s, const std::string &fmt )
  {
    stringstream ss;
    ss << s;
    struct tm tm;
    ss >> std::get_time(&tm, fmt.c_str());
    return (int64_t)mktime(&tm) * SEC;
  }


  std::string Datetime::Time2Str(int64_t time_us, const std::string &fmt)
  {
    stringstream ss;
    time_t t = time_us / SEC;
    auto tm = std::gmtime(&t);
    ss << std::put_time(tm, fmt.c_str());
    return ss.str();
  }


  int64_t Datetime::Str2Time(const std::string &s, const std::string &fmt)
  {
    stringstream ss;
    ss << s;
    struct tm tm;
    ss >> std::get_time(&tm, fmt.c_str());
    return (int64_t)mktime(&tm) * SEC + HOUR * 8; // because mktime include zone
  }
}