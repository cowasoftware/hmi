#include "./logger.h"

namespace three::gl
{
  LoggerLevel Logger::level = LoggerLevel::INFO;

  Logger::Logger()
    : level_(level)
  {
  }
  Logger::Logger(LoggerLevel _level)
    : level_(_level)
  {
  }

  void Logger::SetLevel(LoggerLevel _level)
  {
    level_ = _level;
  }
}