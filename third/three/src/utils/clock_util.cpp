#include "./clock_util.h"
#include <chrono>

std::string ClockUtil::runTime(RunCall call, int count)
{
	auto s = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	for (int i = 0; i < count; i++)
	{
		call();
	}
	auto e = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::stringstream ss;

	ss << e - s << ":" << (e - s) / (float)count;
	return ss.str();
}

int64_t ClockUtil::fps()
{
	static auto s = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - s;
	s += elapsed;
	if (elapsed == 0)
	{
		return 0;
	}

	return 1000 / elapsed;
}
