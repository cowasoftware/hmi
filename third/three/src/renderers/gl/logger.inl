#include <fmt/core.h>

#include "./datetime.h"

namespace three::gl
{
  template <typename... T>
  inline void Logger::Debug(std::string f, T &&...args)
  {
    if (level_ <= LoggerLevel::DEBUG)
    {

      fmt::print("[{}][DEBUG]: ", Datetime::Time2Str(Datetime::GetLocalTimeMS()));
      fmt::print<decltype(std::forward<T>(args))...>(f, std::forward<T>(args)...);
      fmt::print("\n");
    }
  }

  template <typename... T>
  inline void Logger::Info(std::string f, T &&...args)
  {
    if (level_ <= LoggerLevel::INFO)
    {
      fmt::print("[{}][INFO]: ", Datetime::Time2Str(Datetime::GetLocalTimeMS()));
      fmt::print<decltype(std::forward<T>(args))...>(f, std::forward<T>(args)...);
      fmt::print("\n");
    }
  }

  template <typename... T>
  inline void Logger::Warn(std::string f, T &&...args)
  {
    if (level_ <= LoggerLevel::WARN)
    {
      fmt::print("[{}][WARN]: ", Datetime::Time2Str(Datetime::GetLocalTimeMS()));
      fmt::print<decltype(std::forward<T>(args))...>(f, std::forward<T>(args)...);
      fmt::print("\n");
    }
  }

  template <typename... T>
  inline void Logger::Fatal(std::string f, T &&...args)
  {
    if (level_ <= LoggerLevel::FATAL)
    {
      fmt::print("[{}][FATAL]: ", Datetime::Time2Str(Datetime::GetLocalTimeMS()));
      fmt::print<decltype(std::forward<T>(args))...>(f, std::forward<T>(args)...);
      fmt::print("\n");
    }
  }
}