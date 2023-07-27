#pragma once
#include <stdint.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <chrono>

class Util
{
public:
	static uint32_t SystemThreadId();
	static std::string GetName(const std::string& path, int32_t flag);
	static std::string GetCurrentExePath();
	static size_t Replace(std::string& str, const std::string& oldstr, const std::string& newstr);
	static std::string Replace(const char* str, const std::string& oldstr, const std::string& newstr);
	static size_t Replace(std::wstring& str, const std::wstring& oldstr, const std::wstring& newstr);
	static size_t Replace(std::string& str, char ch1, char ch2);
	static std::string MakeUpper(const std::string& src);
	static std::string MakeLower(const std::string& src);
	static std::wstring MakeUpper(const std::wstring& src);
	static std::wstring MakeLower(const std::wstring& src);
	static void Format(std::string& str, const char* fmt, ...);
	static std::string Format(const char* fmt, ...);
	static void Format(std::wstring& str, const wchar_t* fmt, ...);
	static std::wstring Format(const wchar_t* fmt, ...);
	static std::string Int_to_Hex(int32_t val);
	static std::vector<std::string> findFilePath(const std::string& strPath,
		int32_t flag = 3,
		const std::string& fileStr = "",
		const std::function<bool (const std::string&)>& EveryFilePath = nullptr,
		std::vector<std::string>* unVisitPath = nullptr);
	static std::string readFile(const std::string& path);
	static std::string timetToStr(time_t timet, bool isLocal = true);
	static int32_t GetCPUCoreCount();
	static int32_t SystemCommand(const std::string& command, std::string& result, bool isShowCmd = false);
	static std::chrono::high_resolution_clock::time_point GetHighTickCount();
	static int32_t GetHighTickCountMilliRunTime(const std::chrono::high_resolution_clock::time_point& beginTime);
	static int32_t GetHighTickCountMicroRunTime(const std::chrono::high_resolution_clock::time_point& beginTime);
	static int64_t GetHighTickCountNanoRunTime(const std::chrono::high_resolution_clock::time_point& beginTime);
	static int32_t GetMilliRunTime(const std::chrono::high_resolution_clock::time_point& endTime, const std::chrono::high_resolution_clock::time_point& beginTime);
	static int32_t GetMicroRunTime(const std::chrono::high_resolution_clock::time_point& endTime, const std::chrono::high_resolution_clock::time_point& beginTime);
	static int64_t GetNanoRunTime(const std::chrono::high_resolution_clock::time_point& endTime, const std::chrono::high_resolution_clock::time_point& beginTime);
};