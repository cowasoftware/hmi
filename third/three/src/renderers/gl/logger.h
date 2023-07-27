#pragma once

#include <string>

#include <fmt/core.h>


namespace three::gl
{

	enum class LoggerLevel
	{
		DEBUG,
		INFO,
		WARN,
		FATAL,
	};

	class Logger
	{
	public:
		Logger();
		Logger(LoggerLevel level);

		template <typename... T>
		void Debug(std::string, T&&... args);

		template <typename... T>
		void Info(std::string f, T&&... args);

		template <typename... T>

		void Warn(std::string f, T&&... args);

		template <typename... T>
		void Fatal(std::string f, T&&... args);

	public:
		void SetLevel(LoggerLevel level);

	public:
		static LoggerLevel level;
	private:
		LoggerLevel level_;
	};

}

#include "./logger.inl"