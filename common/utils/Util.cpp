#include "Util.h"
#include <thread>
#include <unistd.h>
#include <stdarg.h>
#include <algorithm>
#include <queue>
#include <dirent.h>
#include <dlfcn.h>
#include <codecvt>
#include <locale>
#include <iconv.h>
#include <string.h>
#include <stdarg.h>
#include <codecvt>
#include <locale>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <fstream>

uint32_t Util::SystemThreadId()
{
#ifdef _WIN32
	return ::GetCurrentThreadId();
	//return ((_Thrd_t*)(char*)&(std::this_thread::get_id()))->_Id;
#elif __unix__
	std::thread::id threadId = std::this_thread::get_id();
	return (uint32_t)(*(__gthread_t*)(char*)(&threadId));
#endif
}

std::string Util::GetName(const std::string& path, int32_t flag)
{
	int32_t left = (int32_t)path.find_last_of("/\\");
	std::string name = path.substr(left + 1, path.length() - left - 1);
	int32_t point = (int32_t)name.find_last_of(".");
	switch (flag)
	{
	case 1:
	{
		return name;
	}
	case 2:
	{
		return name.substr(point + 1, point == -1 ? 0 : name.length() - point - 1);
	}
	case 3:
	{
		return name.substr(0, point == -1 ? name.length() : point);
	}
	case 4:
	{
		return path.substr(0, left + 1);
	}
	default:
		return "";
	}
}

std::string Util::GetCurrentExePath()
{
	char szFilePath[1024] = {};
#ifdef _WIN32
	::GetModuleFileNameA(NULL, szFilePath, 1024);
#elif __unix__
	if (::readlink("/proc/self/exe", szFilePath, 1024) == -1)
	{
		printf("readlink error\n");
		return "";
	}
#endif
	return Util::GetName(szFilePath, 4);
}

size_t Util::Replace(std::string& str, const std::string& oldstr, const std::string& newstr)
{
	size_t count = 0;
	size_t pos = 0;
	while (true)
	{
		pos = str.find(oldstr, pos);
		if (pos == std::string::npos)
		{
			break;
		}
		str.replace(pos, oldstr.length(), newstr);
		pos += newstr.length();
		++count;
	}
	return count;
}

std::string Util::Replace(const char* str, const std::string& oldstr, const std::string& newstr)
{
	if (str == nullptr)
	{
		return std::string();
	}
	std::string result = str;
	Replace(result, oldstr, newstr);
	return result;
}

size_t Util::Replace(std::wstring& str, const std::wstring& oldstr, const std::wstring& newstr)
{
	size_t count = 0;
	size_t pos = 0;
	while (true)
	{
		pos = str.find(oldstr, pos);
		if (pos == std::wstring::npos)
		{
			break;
		}
		str.replace(pos, oldstr.length(), newstr);
		pos += newstr.length();
		++count;
	}
	return count;
}

size_t Util::Replace(std::string& str, char ch1, char ch2)
{
	size_t count = 0;
	for (size_t pos = 0; pos != str.size(); ++pos)
	{
		if (str[pos] == ch1)
		{
			str[pos] = ch2;
			++count;
		}
	}
	return count;
}

void Util::Format(std::string& str, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
#ifdef _WIN32
	int size = _vscprintf(fmt, args);
#elif __unix__
	va_list argcopy;
	va_copy(argcopy, args);
	int size = vsnprintf(nullptr, 0, fmt, argcopy);
#endif
	//?resize分配后string类会自动在最后分配\0，resize(5)则总长6
	str.resize(size);
	if (size != 0)
	{
#ifdef _WIN32
		//?即便分配了足够内存，长度必须加1，否则会崩溃
		vsprintf_s(&str[0], size + 1, fmt, args);
#elif __unix__
		vsnprintf(&str[0], size + 1, fmt, args);
#endif
	}
	va_end(args);
}

std::string Util::Format(const char* fmt, ...)
{
	std::string result;
	va_list args;
	va_start(args, fmt);
#ifdef _WIN32
	int size = _vscprintf(fmt, args);
#elif __unix__
	va_list argcopy;
	va_copy(argcopy, args);
	int size = vsnprintf(nullptr, 0, fmt, argcopy);
#endif
	//?resize分配后string类会自动在最后分配\0，resize(5)则总长6
	result.resize(size);
	if (size != 0)
	{
#ifdef _WIN32
		//?即便分配了足够内存，长度必须加1，否则会崩溃
		vsprintf_s(&result[0], size + 1, fmt, args);
#elif __unix__
		vsnprintf(&result[0], size + 1, fmt, args);
#endif
	}
	va_end(args);
	return result;
}

std::string Util::MakeUpper(const std::string& src)
{
	std::string dst;
#if defined _MSC_VER && (_MSC_VER < 1800)
	return dst;
#endif
	//如果dst是有值的话则第三个参数传dst.begin()，从头开始覆盖
	std::transform(src.begin(), src.end(), std::back_inserter(dst), ::toupper);
	return dst;
}

std::string Util::MakeLower(const std::string& src)
{
	std::string dst;
#if defined _MSC_VER && (_MSC_VER < 1800)
	return dst;
#endif
	std::transform(src.begin(), src.end(), std::back_inserter(dst), ::tolower);
	return dst;
}

std::wstring Util::MakeUpper(const std::wstring& src)
{
	std::wstring dst;
#if defined _MSC_VER && (_MSC_VER < 1800)
	return dst;
#endif
	std::transform(src.begin(), src.end(), std::back_inserter(dst), ::toupper);
	return dst;
}

std::wstring Util::MakeLower(const std::wstring& src)
{
	std::wstring dst;
#if defined _MSC_VER && (_MSC_VER < 1800)
	return dst;
#endif
	std::transform(src.begin(), src.end(), std::back_inserter(dst), ::tolower);
	return dst;
}

std::string Util::Int_to_Hex(int32_t val)
{
	std::stringstream stream;
	stream << std::hex << val;
	return stream.str();
}

static void Split(std::vector<std::string>& result, const std::string& splitString, char separate_character)
{
	result.clear();
	size_t lastPosition = 0;
	int32_t index = -1;
	while (-1 != (index = (int32_t)splitString.find(separate_character, lastPosition)))
	{
		result.push_back(splitString.substr(lastPosition, index - lastPosition));
		lastPosition = index + 1;
	}
	result.push_back(splitString.substr(lastPosition));
}

std::vector<std::string> Util::findFilePath(const std::string& strPath,
	int32_t flag,
	const std::string& fileStr,
	const std::function<bool (const std::string&)>& EveryFilePath,
	std::vector<std::string>* unVisitPath)
{
	std::string dir = strPath;
	if (dir.empty())
	{
		dir = GetCurrentExePath();
	}
#ifdef _WIN32
	char level = '\\';
#elif __unix__
	char level = '/';
#endif
	if (dir.back() != level)
	{
		dir.push_back(level);
	}
#ifdef _WIN32
	dir.push_back('*');
#endif

	if (unVisitPath != nullptr)
	{
		unVisitPath->clear();
	}

	std::vector<std::string> result;
#ifdef _WIN32
	_finddata_t fileDir;
#elif __unix__
	struct dirent *pDirent = nullptr;
#endif

	std::queue<std::string> queue_dir;
	queue_dir.push(std::string(dir));

	while (!queue_dir.empty())
	{
		std::string curDir = queue_dir.front();
		queue_dir.pop();
#ifdef _WIN32
		auto lfDir = _findfirst(curDir.c_str(), &fileDir);
#elif __unix__
		DIR* pDir = opendir(curDir.c_str());
#endif

#ifdef _WIN32
		if (lfDir == -1)
#elif __unix__
		if (pDir == nullptr)
#endif
		{
			if (unVisitPath != nullptr)
			{
				curDir.pop_back();
				unVisitPath->emplace_back(curDir);
			}
			continue;
		}

		std::vector<std::string> vecLowerFileStr;
		if (flag == 2)
		{
			std::string lowerFileStr;
			std::transform(fileStr.begin(), fileStr.end(), std::back_inserter(lowerFileStr), ::tolower);
			Split(vecLowerFileStr, lowerFileStr, '.');
		}

#ifdef _WIN32
		while (_findnext(lfDir, &fileDir) == 0)
#elif __unix__
		while ((pDirent = readdir(pDir)) != 0)
#endif
		{
#ifdef _WIN32
			std::string strName = fileDir.name;
#elif __unix__
			std::string strName = pDirent->d_name;
#endif
#ifdef _WIN32
			if ((fileDir.attrib >= 16 && fileDir.attrib <= 23) || (fileDir.attrib >= 48 && fileDir.attrib <= 55))
#elif __unix__
			if (pDirent->d_type == DT_DIR)
#endif
			{
				if (strName == "." || strName == "..")
				{
					continue;
				}
				std::string tmpstr = curDir;
#ifdef _WIN32
				tmpstr.pop_back();
#endif
				tmpstr.append(strName);
				tmpstr.push_back(level);
#ifdef _WIN32
				tmpstr.push_back('*');
#endif
				queue_dir.emplace(tmpstr);
				continue;
			}
			bool isExit = false;
			std::string tmpfilename = curDir;
#ifdef _WIN32
			tmpfilename.pop_back();
#endif
			switch (flag)
			{
			case 1:
			{
				if (strName == fileStr)
				{
					tmpfilename.append(strName);
					if (EveryFilePath != nullptr)
					{
						isExit = EveryFilePath(tmpfilename);
					}
					result.emplace_back(tmpfilename);
				}
			}
			break;
			case 2:
			{
				std::string nameSuffix = GetName(strName, 2);
				std::string lowerNameSuffix;
				std::transform(nameSuffix.begin(), nameSuffix.end(), std::back_inserter(lowerNameSuffix), ::tolower);
				if ((vecLowerFileStr.empty() && lowerNameSuffix.empty()) ||
					(!vecLowerFileStr.empty() && std::find(vecLowerFileStr.begin(), vecLowerFileStr.end(), lowerNameSuffix) != vecLowerFileStr.end()))
				{
					tmpfilename.append(strName);
					if (EveryFilePath != nullptr)
					{
						isExit = EveryFilePath(tmpfilename);
					}
					result.emplace_back(tmpfilename);
				}
			}
			break;
			case 3:
			{
				tmpfilename.append(strName);
				if (EveryFilePath != nullptr)
				{
					isExit = EveryFilePath(tmpfilename);
				}
				result.emplace_back(tmpfilename);
			}
			break;
			default:
				break;
			}
			if (isExit)
			{
				break;
			}
		}
#ifdef _WIN32
		_findclose(lfDir);
#elif __unix__
		closedir(pDir);
#endif
	}
	return result;
}

std::string Util::readFile(const std::string& path)
{
	FILE* file = fopen(path.c_str(), "rb");
	if (file == nullptr)
	{
		return "";
	}
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	std::string result;
	result.resize(length);
	fread(&result[0], 1, length, file);
	fclose(file);
	return result;
}

std::string Util::timetToStr(time_t timet, bool isLocal)
{
	char buf[128] = {};
	if (isLocal)
	{
		//转为本地时间
		tm* local = localtime(&timet);
		sprintf(buf,
			"%04d-%02d-%d %02d:%02d:%02d",
			local->tm_year + 1900,
			local->tm_mon + 1,
			local->tm_mday,
			local->tm_hour,
			local->tm_min,
			local->tm_sec);
	}
	else
	{
		//转为格林威治时间
		strftime(buf, 64, "%Y-%m-%d %H:%M:%S", gmtime(&timet));
	}
	return buf;
}

int32_t Util::GetCPUCoreCount()
{
#ifdef _WIN32
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
#elif __unix__
	std::string result;
	if (SystemCommand("grep 'processor' /proc/cpuinfo | sort -u | wc -l", result) == -1 || result.empty())
	{
		return 0;
	}
	result.pop_back();
	return atoi(result.c_str());
#endif
}

int32_t Util::SystemCommand(const std::string& command, std::string& result, bool isShowCmd)
{
	if (command.size() == 0)
	{
		//command is empty
		return -1;
	}
	if (!isShowCmd)
	{
#ifdef _WIN32
		result.clear();
		SECURITY_ATTRIBUTES sa;
		HANDLE hRead, hWrite;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		if (!CreatePipe(&hRead, &hWrite, &sa, 0))
		{
			return -1;
		}

		STARTUPINFOA si;
		PROCESS_INFORMATION pi;
		si.cb = sizeof(STARTUPINFO);
		GetStartupInfoA(&si);
		si.hStdError = hWrite;
		si.hStdOutput = hWrite;
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		//关键步骤，CreateProcess函数参数意义请查阅MSDN   
		if (!CreateProcessA(NULL, (char*)command.c_str(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
		{
			return -1;
		}
		CloseHandle(hWrite);
		char buffer[4096] = { 0 };
		DWORD bytesRead;
		while (true)
		{
			memset(buffer, 0, strlen(buffer));
			if (ReadFile(hRead, buffer, 4095, &bytesRead, NULL) == NULL)
			{
				break;
			}
			//buffer中就是执行的结果，可以保存到文本，也可以直接输出   
			result += buffer;
			Sleep(10);
		}
		return 0;
#endif
	}
	char buffer[4096] = {};
	std::string fresult;
#ifdef _WIN32
	FILE* pin = _popen(command.c_str(), "r");
#elif __unix__
	FILE* pin = popen(command.c_str(), "r");
#endif
	if (!pin)
	{
		//popen failed
		return -1;
	}
	result.clear();
	while (!feof(pin))
	{
		if (fgets(buffer, sizeof(buffer), pin) != nullptr)
		{
			fresult += buffer;
		}
	}
	result = fresult;
	//-1:pclose failed; else shell ret
#ifdef _WIN32
	return _pclose(pin);
#elif __unix__
	return pclose(pin);
#endif
}

std::chrono::high_resolution_clock::time_point Util::GetHighTickCount()
{
	return std::chrono::high_resolution_clock::now();
}

int32_t Util::GetHighTickCountMilliRunTime(const std::chrono::high_resolution_clock::time_point& beginTime)
{
	return (int32_t)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - beginTime).count();
}

int32_t Util::GetHighTickCountMicroRunTime(const std::chrono::high_resolution_clock::time_point& beginTime)
{
	return (int32_t)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - beginTime).count();
}

int64_t Util::GetHighTickCountNanoRunTime(const std::chrono::high_resolution_clock::time_point& beginTime)
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - beginTime).count();
}

int32_t Util::GetMilliRunTime(const std::chrono::high_resolution_clock::time_point& endTime, const std::chrono::high_resolution_clock::time_point& beginTime)
{
	return (int32_t)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();
}

int32_t Util::GetMicroRunTime(const std::chrono::high_resolution_clock::time_point& endTime, const std::chrono::high_resolution_clock::time_point& beginTime)
{
	return (int32_t)std::chrono::duration_cast<std::chrono::microseconds>(endTime - beginTime).count();
}

int64_t Util::GetNanoRunTime(const std::chrono::high_resolution_clock::time_point& endTime, const std::chrono::high_resolution_clock::time_point& beginTime)
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime).count();
}